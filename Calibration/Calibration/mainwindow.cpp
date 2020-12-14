#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBOx>
#include <QTextStream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
	m_statusLabel = new QLabel(this);
	ui.statusBar->addWidget(m_statusLabel);	

	connect(ui.pushButton_imageFile, &QPushButton::clicked, this, &MainWindow::ptn_imageFile_clicked);
	connect(ui.pushButton_leftIntrinsic, &QPushButton::clicked, this, &MainWindow::ptn_leftIntrinsic_clicked);
	connect(ui.pushButton_rightIntrinsic, &QPushButton::clicked, this, &MainWindow::ptn_rightIntrinsic_clicked);
	connect(ui.pushButton_leftCorners, &QPushButton::clicked, this, &MainWindow::ptn_leftCorners_clicked);
	connect(ui.pushButton_rightCorners, &QPushButton::clicked, this, &MainWindow::ptn_rightCorners_clicked);
	connect(ui.pushButton_internalCal, &QPushButton::clicked, this, &MainWindow::ptn_internalCal_clicked);
	connect(ui.pushButton_externalCal, &QPushButton::clicked, this, &MainWindow::ptn_externalCal_clicked);
	connect(ui.pushButton_savePath, &QPushButton::clicked, this, &MainWindow::ptn_savePath_clicked);
	connect(ui.pushButton_leftCoords, &QPushButton::clicked, this, &MainWindow::ptn_leftCoords_clicked);
	connect(ui.pushButton_rightCoords, &QPushButton::clicked, this, &MainWindow::ptn_rightCoords_clicked);
	connect(ui.pushButton_projectionFile, &QPushButton::clicked, this, &MainWindow::ptn_projectionFile_clicked);
	connect(ui.pushButton_reconstuctionCal, &QPushButton::clicked, this, &MainWindow::ptn_reconstuctionCal_clicked);
}

void MainWindow::ptn_imageFile_clicked() {
	m_imageFileList = QFileDialog::getOpenFileNames(this, tr("选择标定图片"), tr("/"), tr("图片文件(*.bmp);;所有文件（*.*);;"));

	if (m_imageFileList.size())
	{
		int imgNumber = m_imageFileList.size();
		ui.lineEdit_imageFile->setText(m_imageFileList[0]+"\t"+QString::number(imgNumber)+"张图片");

		QFileInfo fileinfo = QFileInfo(m_imageFileList[0]);
		m_internalSavePath = creatNewPath(fileinfo.absolutePath());
	}
}

void MainWindow::ptn_leftCorners_clicked() {
	m_leftCornerPath = QFileDialog::getOpenFileNames(this, tr("选择左相机角点坐标文件"), tr("/"), tr("文件(*.txt);;所有文件（*.*);;"));
	if (m_leftCornerPath.size()){
		ui.lineEdit_leftCorners->setText(m_leftCornerPath[0]);
	}

}


void MainWindow::ptn_rightCorners_clicked() {
	m_rightCornerPath = QFileDialog::getOpenFileNames(this, tr("选择右相机角点坐标文件"), tr("/"), tr("文件(*.txt);;所有文件（*.*);;"));
	if (m_rightCornerPath.size()) {
		ui.lineEdit_rightCorners->setText(m_rightCornerPath[0]);
	}

}


void MainWindow::ptn_leftIntrinsic_clicked() {
	m_leftIntrinsicPath = QFileDialog::getOpenFileName(this, tr("选择左相机内参文件"), tr("/"), tr("文件(*.txt);;所有文件（*.*);;"));

	if (!m_leftIntrinsicPath.isEmpty()) {
		ui.lineEdit_leftIntrinsic->setText(m_leftIntrinsicPath);
	}

}


void MainWindow::ptn_rightIntrinsic_clicked() {
	m_rightIntrinsicPath = QFileDialog::getOpenFileName(this, tr("选择右相机内参文件"), tr("/"), tr("文件(*.txt);;所有文件（*.*);;"));
	if (!m_rightIntrinsicPath.isEmpty()) {
		ui.lineEdit_rightIntrinsic->setText(m_rightIntrinsicPath);
	}
}


void MainWindow::ptn_internalCal_clicked() {
	updateChessboardParameters();
	m_statusLabel->setText("内参计算中......");
	QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

	String strSavePath = m_internalSavePath.toStdString();
	int imageNumber = m_imageFileList.size();
	
	Size image_size;//图像尺寸	
	Size board_size = Size(m_widthPointNumber, m_heightPointNumber);//标定板每行、列的角点数	
	vector<Point2f> corners;//缓存每张图上的角点	
	vector<vector<Point2f>> allCorners;//保存检测到的所有角点	

	for (int i = 0; i < imageNumber; i++)
	{
		Mat image = imread(m_imageFileList[i].toStdString(), CV_8U);
		if (i == 0)	{
			m_imgWidth = image_size.width = image.cols;
			m_imgHeight = image_size.height = image.rows;
		}

		//提取角点
		//cv::findCirclesGrid(image, board_size, corners, CALIB_CB_SYMMETRIC_GRID);
		cv::findChessboardCorners(image, board_size, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);		
		allCorners.push_back(corners);//保存亚像素角点

		saveCornerData(m_imageFileList[i], m_internalSavePath, corners);//保存角点坐标至txt文件
	}

	//以下是摄像机标定

	/* 保存标定板上角点的三维坐标 */
	vector<vector<Point3f>> object_points;

	/*内外参数*/
	/* 摄像机内参数矩阵 */
	Mat intrinsicMatrix = Mat(3, 3, CV_64FC1, Scalar::all(0));

	/* 摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
	Mat distortionCoeffs = Mat(1, 5, CV_64FC1, Scalar::all(0));

	
	vector<Mat> transMat;//每幅图像的平移向量
	vector<Mat> rotationMat;//每幅图像的旋转向量

	//初始化标定板上角点的三维坐标
	//将世界坐标系建立在标定板上，标定板面的z坐标为0
	for (int i = 0; i < imageNumber; i++)
	{
		vector<Point3f> tempPointSet;
		for (int rows = 0; rows < board_size.height; rows++)
		{
			for (int columns = 0; columns < board_size.width; columns++)
			{
				Point3f realPoint;
				/* 假设标定板放在世界坐标系中z=0的平面上 */
				realPoint.x = columns * m_chessboardSize;//16代表标定板单元格尺寸
				realPoint.y = rows * m_chessboardSize;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		object_points.push_back(tempPointSet);
	}

	/* 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板 */

	// 每幅图像中角点的数量
	vector<int> image_point_counts(imageNumber, board_size.width*board_size.height);

	//前3参数为输入参数： 真实三维点 标定板角点图像坐标 图像大小
	//后4参数为输出参数： 相机内参矩阵 畸变向量 旋转向量（世界坐标系 到 相机坐标系） 平移向量（世界坐标系 到 相机坐标系） 
	cv::calibrateCamera(object_points, allCorners, image_size, intrinsicMatrix, distortionCoeffs, rotationMat, transMat, 0);
	saveIntrinsicParameters(m_internalSavePath, intrinsicMatrix, distortionCoeffs);//将内参数据保存至txt文件

	m_statusLabel->setText("");
}


/************************外参标定**************************/
void MainWindow::ptn_externalCal_clicked() {
	updateChessboardParameters();
	m_statusLabel->setText("外参计算中......");
	QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

	m_imgWidth = 2448;
	m_imgHeight = 2050;

	Mat leftCameraMatrix = Mat(3, 3, CV_64FC1, Scalar::all(0));
	Mat rightCameraMatrix = Mat(3, 3, CV_64FC1, Scalar::all(0));
	Mat leftDistortCoeffs = Mat(1, 5, CV_64FC1, Scalar::all(0));
	Mat rightDistortCoeffs = Mat(1, 5, CV_64FC1, Scalar::all(0));
	getCameraMatrix(m_leftIntrinsicPath, leftCameraMatrix, leftDistortCoeffs);
	getCameraMatrix(m_rightIntrinsicPath, rightCameraMatrix, rightDistortCoeffs);

	vector<Point3f> worldPoints;
	for (int rows = 0; rows < m_heightPointNumber; ++rows)
	{
		for (int cols = 0; cols < m_widthPointNumber; ++cols)
		{
			Point3f point;
			point.x = cols * m_chessboardSize;
			point.y = rows * m_chessboardSize;
			point.z = 0;

			worldPoints.push_back(point);
		}
	}
	vector<vector<Point3f>> allWorldPoints(m_leftCornerPath.size(), worldPoints);

	//导入40*81个点相机圆心坐标
	vector<vector<Point2f>> cornerCoordinates_L;
	vector<vector<Point2f>> cornerCoordinates_R;

	for (int i = 0; i < m_leftCornerPath.size(); ++i)
	{
		QVector<QPointF> tempLeftPoints = getCornerCoordinates(m_leftCornerPath[i]);
		QVector<QPointF> tempRightPoints = getCornerCoordinates(m_rightCornerPath[i]);
		vector<Point2f> leftCircleCenter;
		vector<Point2f> rightCircleCenter;

		for (int count=0;count< tempLeftPoints.size();++count) {
			leftCircleCenter.push_back(Point2f(tempLeftPoints[count].x(), tempLeftPoints[count].y()));
			rightCircleCenter.push_back(Point2f(tempRightPoints[count].x(), tempRightPoints[count].y()));
		}

		cornerCoordinates_L.push_back(leftCircleCenter);
		cornerCoordinates_R.push_back(rightCircleCenter);
	}

	Size imgSize(m_imgWidth, m_imgHeight);

	Mat R = (Mat_<float>(3, 3) << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);//旋转矩阵
	Mat T = (Mat_<float>(3, 1) << 0.0, 0.0, 0.0);//平移向量
	Mat E = (Mat_<float>(3, 3) << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
	Mat F = (Mat_<float>(3, 3) << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

	stereoCalibrate(allWorldPoints, cornerCoordinates_L, cornerCoordinates_R, leftCameraMatrix, leftDistortCoeffs, rightCameraMatrix, rightDistortCoeffs, imgSize, R, T, E, F, CALIB_FIX_INTRINSIC);

	saveExtrinsicParameters(m_externalSavePath, R, T);
	saveProjectionMatrix(m_externalSavePath, F, leftCameraMatrix, rightCameraMatrix, R, T);

	m_statusLabel->setText("");
}

void MainWindow::ptn_savePath_clicked() {
	m_externalSavePath = QFileDialog::getSaveFileName(this, tr("请选择双相机外参（旋转矩阵+平移向量）数据保存路径"), "", tr("*.txt")); //选择路径
	if (!m_externalSavePath.isEmpty()) {
		ui.lineEdit_savePath->setText(m_externalSavePath);
	}
}

QString MainWindow::getPath_noSuffix(QString path) {
	QFileInfo fileinfo = QFileInfo(path);
	QString temp = fileinfo.path();
	temp += "/";
	temp += fileinfo.baseName();

	return temp;
}


QString MainWindow::creatNewPath(QString path) {
	int i_count = 0;
	bool isFinished = false;

	QString dir_str = path;
	QDir dir;
	while (1)
	{
		QString strTemp = "";

		if (i_count < 10) {
			strTemp = "/Result_0" + QString::number(i_count);
		}
		else {
			strTemp = "/Result_" + QString::number(i_count);
		}
		strTemp = path + strTemp;

		if (!dir.exists(strTemp)) {
			if (dir.mkpath(strTemp)) {
				isFinished = true;
				path = strTemp;
				break;
			}

		}
		i_count++;
	}
	return path;
}


//filePath：图片路径
//savePath：文件保存文件夹，txt文件名和图片名称一样
//corners：角点
void MainWindow::saveCornerData(QString filePath, QString savePath, const vector<Point2f> &corners)
{
	QFileInfo fileInfo = QFileInfo(filePath);
	QString baseName = fileInfo.baseName();
	savePath += "/" + baseName + ".txt";

	QString data("Index\tX\tY\n");
	for (int i = 0; i < corners.size(); ++i) {
		data += QString::number(i+1) + "\t";
		data += QString::number(corners[i].x, 'f', 3) + "\t";
		data += QString::number(corners[i].y, 'f', 3) + "\n";
	}	

	QFile file(savePath);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(data.toUtf8());
}


//intrinsicMatrix: 摄像机内参数矩阵
//  |  fx   0   Cx   |
//  |  0    fy  Cy   |
//  |  0    0   1    |
//distortionCoeffs:摄像机的5个畸变系数：k1,k2,p1,p2,k3 

void MainWindow::saveIntrinsicParameters(QString savePath, const Mat &intrinsicMatrix, const Mat &distortionCoeffs) 
{
	QString data("Intrinsic matrix\n");
	for (int i=0;i<3;i++) {
		for (int j = 0; j < 3; j++)	{
			data += QString::number(intrinsicMatrix.at<double>(i, j), 'f', 8);
			data += "\t";
		}
		data += "\n";
	}

	data += "k1, k2, p1, p2, k3\n";
	data += QString::number(distortionCoeffs.at<double>(0, 0), 'f', 8) + "\t";
	data += QString::number(distortionCoeffs.at<double>(0, 1), 'f', 8) + "\t";
	data += QString::number(distortionCoeffs.at<double>(0, 2), 'f', 8) + "\t";
	data += QString::number(distortionCoeffs.at<double>(0, 3), 'f', 8) + "\t";
	data += QString::number(distortionCoeffs.at<double>(0, 4), 'f', 8) + "\n";


	savePath += "/_intrinsicParameters.txt";
	QFile file(savePath);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(data.toUtf8());
}


void MainWindow::updateChessboardParameters() {
	m_widthPointNumber = ui.spinBox_widthPoints->value();
	m_heightPointNumber = ui.spinBox_heightPoints->value();
	m_chessboardSize = ui.spinBox_chessboardSize->value();
}

void MainWindow::getCameraMatrix(QString path, Mat &cameraMatrix, Mat &distortionCoeff) {

	QFile readFile(path);
	if (!readFile.open(QIODevice::ReadOnly | QFile::Truncate | QFile::Text)) {
		QMessageBox::information(nullptr, "Warning", "Fail to read the file");
		return;
	}

	QTextStream readStream(&readFile);
	QString line("");

	line = readStream.readLine();
	for (int i=0;i<3;i++) {
		line = readStream.readLine();
		if (!line.isEmpty()) {
			QStringList list = line.split(QRegExp("[,=\t]+"), QString::SkipEmptyParts);
			cameraMatrix.at<double>(i, 0) = list.at(0).toDouble();
			cameraMatrix.at<double>(i, 1) = list.at(1).toDouble();
			cameraMatrix.at<double>(i, 2) = list.at(2).toDouble();
		}
	}

	line = readStream.readLine();
	line = readStream.readLine();
	if (!line.isEmpty()) {
		QStringList list = line.split(QRegExp("[,=\t]+"), QString::SkipEmptyParts);
		for (int i = 0; i < 5; i++)
			distortionCoeff.at<double>(0, i) = list.at(i).toDouble();
	}

	readFile.close();
}


QVector<QPointF> MainWindow::getCornerCoordinates(QString path) {
	QVector<QPointF> temp;
	
	QFile readFile(path);
	if (!readFile.open(QIODevice::ReadOnly | QFile::Truncate | QFile::Text)) {
		QMessageBox::information(nullptr, "Warning", "Fail to read the file");
		return temp;
	}

	QTextStream readStream(&readFile);
	QString line("");

	line = readStream.readLine();
	while(!readStream.atEnd()) {
		line = readStream.readLine();
		if (!line.isEmpty()) {
			QStringList list = line.split(QRegExp("[,=;\t]+"), QString::SkipEmptyParts);
			if (list.size()==3)
				temp.push_back(QPointF(list.at(1).toDouble(), list.at(2).toDouble()));
		}
	}
	readFile.close();

	return temp;
}


QVector<QVector<double>> MainWindow::matrix_multiply(const QVector<QVector<double>> &matrix1, const QVector<QVector<double>> &matrix2)
{
	int row1 = matrix1.size();
	int col1 = matrix1[0].size();
	int col2 = matrix2[0].size();
	QVector<QVector<double>> result(row1);
	for (int i = 0; i < row1; i++)
		result[i].resize(col2);

	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++)
		{
			result[i][j] = 0;
			QVector<double> m1, m2;
			for (int count = 0; count < col1; count++)
				m1.push_back(matrix1[i][count]);
			for (int count = 0; count < col1; count++)
				m2.push_back(matrix2[count][j]);
			for (int count = 0; count < col1; count++)
				result[i][j] += m1[count] * m2[count];
		}
	}

	return result;

}


void MainWindow::saveExtrinsicParameters(QString savePath, const Mat &R, const Mat &T) {
	Mat rotationVector;
	cv::Rodrigues(R, rotationVector);

	QString data = "Rotation matrix:\n";
	for (int i=0;i<3;i++) {
		for (int j = 0; j < 3; j++)	{
			data += QString::number(R.at<double>(i, j), 'f', 4);
			data += "\t";
		}
		data += "\n";
	}

	data += "Rotation vector:\n";
	for (int i = 0; i < 3; i++)
		data += QString::number(rotationVector.at<double>(i, 0), 'f', 6) + "\n";


	data += "Translation vector:\n";
	for (int i = 0; i < 3; i++)
		data += QString::number(T.at<double>(i, 0), 'f', 2) + "\n";

	QFile file(savePath);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(data.toUtf8());
}

void MainWindow::saveProjectionMatrix(QString savePath, const Mat &Fundamental, const Mat &leftCameraMatrix, const Mat &rightCameraMatrix, const Mat &R, const Mat &T)
{
	QFileInfo fileinfo = QFileInfo(savePath);
	savePath = fileinfo.path();
	savePath += "/_projectionMatrix.txt";

	QVector<QVector<double>> mainProjectionMatrix(3);
	QVector<QVector<double>> transAndRotation(3);
	QVector<QVector<double>> cameraMatrix_R(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mainProjectionMatrix[i].push_back(leftCameraMatrix.at<double>(i, j));
			cameraMatrix_R[i].push_back(rightCameraMatrix.at<double>(i, j));
			transAndRotation[i].push_back(R.at<double>(i, j));			
		}
	}			
	mainProjectionMatrix[0].push_back(0.0);
	mainProjectionMatrix[1].push_back(0.0);
	mainProjectionMatrix[2].push_back(0.0);


	transAndRotation[0].push_back(T.at<double>(0, 0));
	transAndRotation[1].push_back(T.at<double>(1, 0));
	transAndRotation[2].push_back(T.at<double>(2, 0));

	QVector<QVector<double>> assistProjectionMatrix = matrix_multiply(cameraMatrix_R, transAndRotation);

	QString data = "Fundamental Matrix:\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			data += QString::number(Fundamental.at<double>(i, j), 'f', 6);
			data += "\t";
		}
		data += "\n";
	}

	data += "Main Projection Matrix:\n";
	for (int i = 0; i < mainProjectionMatrix.size(); i++) {
		for (int j = 0; j < mainProjectionMatrix[0].size(); j++) {
			data += QString::number(mainProjectionMatrix[i][j], 'f', 8);
			data += "\t";
		}
		data += "\n";
	}

	data += "Assist Projection Matrix:\n";
	for (int i = 0; i < assistProjectionMatrix.size(); i++) {
		for (int j = 0; j < assistProjectionMatrix[0].size(); j++) {
			data += QString::number(assistProjectionMatrix[i][j], 'f', 8);
			data += "\t";
		}
		data += "\n";
	}


	QFile file(savePath);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(data.toUtf8());
	file.close();	
}


void MainWindow::ptn_leftCoords_clicked() {
	m_leftCoordPath = QFileDialog::getOpenFileName(this, tr("选择左相机像素坐标文件"), tr("/"), tr("文件(*.txt);;所有文件（*.*);;"));

	if (!m_leftCoordPath.isEmpty())
		ui.lineEdit_leftCoords->setText(m_leftCoordPath);
}


void MainWindow::ptn_rightCoords_clicked() {
	m_rightCoordPath = QFileDialog::getOpenFileName(this, tr("选择右相机像素坐标文件"), tr("/"), tr("文件(*.txt);;所有文件（*.*);;"));

	if (!m_rightCoordPath.isEmpty())
		ui.lineEdit_rightCoords->setText(m_rightCoordPath);

}

void MainWindow::ptn_projectionFile_clicked() {
	m_projectionFilePath = QFileDialog::getOpenFileName(this, tr("选择投影矩阵文件"), tr("/"), tr("文件(*.txt);;所有文件（*.*);;"));

	if (!m_projectionFilePath.isEmpty())
		ui.lineEdit_projectionFile->setText(m_projectionFilePath);

}


void MainWindow::ptn_reconstuctionCal_clicked() {

	m_statusLabel->setText("三维重建中......");
	QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

	//从文件中读取左右相机的投影矩阵
	QVector<double> mainProjectionMatrix;
	QVector<double> assistProjectionMatrix;
	getProjectionMatrix(m_projectionFilePath, mainProjectionMatrix, assistProjectionMatrix);

	QVector<QPointF> leftImgPoints = readDataFromFile(1, m_leftCoordPath);
	QVector<QPointF> rightImgPoints = readDataFromFile(1, m_rightCoordPath);
	int number = leftImgPoints.size() > rightImgPoints.size() ? rightImgPoints.size() : leftImgPoints.size();

	QVector<Point_3d> coordinates_3d;
	for (int i = 0; i < number; i++)
	{
		QVector<double> temp3dPoint(3);
		reconstruction(leftImgPoints[i], rightImgPoints[i], mainProjectionMatrix, assistProjectionMatrix, temp3dPoint);
		Point_3d temp;
		temp.x = temp3dPoint[0];
		temp.y = temp3dPoint[1];
		temp.z = temp3dPoint[2];
		coordinates_3d.push_back(temp);
	}

	QFileInfo fileinfo = QFileInfo(m_projectionFilePath);
	QString savePath = fileinfo.path();
	save3dPointsInfo(savePath, coordinates_3d);

	m_statusLabel->setText("");
}


void MainWindow::getProjectionMatrix(QString path, QVector<double> &mainProjection, QVector<double> &assistProjection) {
	mainProjection.clear();
	assistProjection.clear();

	QFile readFile(path);
	if (!readFile.open(QIODevice::ReadOnly | QFile::Truncate | QFile::Text)) {
		QMessageBox::information(nullptr, "Warning", "Fail to read the file");
		return;
	}

	QTextStream readStream(&readFile);
	QString line("");
	for (int i=0;i<5;i++)
		line = readStream.readLine();

	for (int i = 0; i < 3; i++) {
		line = readStream.readLine();
		if (!line.isEmpty()) {
			QStringList list = line.split(QRegExp("[, ;\t]+"), QString::SkipEmptyParts);
			for (int aa = 0; aa < list.size(); aa++)
				mainProjection.push_back(list.at(aa).toDouble());
		}
	}

	line = readStream.readLine();
	for (int i = 0; i < 3; i++) {
		line = readStream.readLine();
		if (!line.isEmpty()) {
			QStringList list = line.split(QRegExp("[, ;\t]+"), QString::SkipEmptyParts);
			for (int aa = 0; aa < list.size(); aa++)
				assistProjection.push_back(list.at(aa).toDouble());
		}
	}

	readFile.close();
}


QVector<QPointF> MainWindow::readDataFromFile(int skipNumber, QString path) {
	int i = 0;
	QVector<QPointF> tempPoints;
	QFile readFile(path);

	if (!readFile.open(QIODevice::ReadOnly | QFile::Truncate | QFile::Text)) {
		QMessageBox::information(nullptr, "Warning", "Fail to read the file");
	}

	QTextStream readStream(&readFile);
	QString line("");

	for (int i = 0; i < skipNumber; i++)
		line = readStream.readLine();

	while (!readStream.atEnd()) {
		line = readStream.readLine();
		if (!line.isEmpty()) {
			QStringList list = line.split(QRegExp("[, ;\t]+"), QString::SkipEmptyParts);
			list.pop_front();
			tempPoints.push_back(QPointF(list.at(0).toDouble(), list.at(1).toDouble()));
		}
	}

	readFile.close();

	return tempPoints;
}

void MainWindow::save3dPointsInfo(QString savePath, const QVector<Point_3d> &points) {
	QFile file_coord(savePath + "/Coordinates_3d.txt");
	QFile file_dis(savePath + "/Displacement_3d.txt");

	file_coord.open(QIODevice::WriteOnly | QIODevice::Text);
	file_dis.open(QIODevice::WriteOnly | QIODevice::Text);

	QString str_coord("");
	QString str_dis("");

	Point_3d initPoint = points[0];

	str_coord = "Index\tx\ty\tz\n";
	str_dis = "Index\tX\tY\tZ\tDis\n";
	for (int i = 0; i < points.size(); i++)
	{
		str_coord += QString::number(i + 1) + "\t";
		str_coord += QString::number(points[i].x, 'f', 5) + "\t";
		str_coord += QString::number(points[i].y, 'f', 5) + "\t";
		str_coord += QString::number(points[i].z, 'f', 5) + "\n";

		double x = points[i].x - initPoint.x;
		double y = points[i].y - initPoint.y;
		double z = points[i].z - initPoint.z;
		double dis = sqrt(x*x + y * y + z * z);
		str_dis += QString::number(i + 1) + "\t";
		str_dis += QString::number(x, 'f', 5) + "\t";
		str_dis += QString::number(y, 'f', 5) + "\t";
		str_dis += QString::number(z, 'f', 5) + "\t";
		str_dis += QString::number(dis, 'f', 5) + "\n";
	}


	file_coord.write(str_coord.toUtf8());
	file_dis.write(str_dis.toUtf8());
}


//利用opencv的函数得到三维坐标
void MainWindow::reconstruction(const QPointF &pos1, const QPointF &pos2, const QVector<double> &p_matrix1, const QVector<double> &p_matrix2, QVector<double> &world_coor) {

	cv::Mat project1(3, 4, CV_64FC1);
	cv::Mat project2(3, 4, CV_64FC1);
	std::vector<cv::Point2f> points1;
	std::vector<cv::Point2f> points2;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			project1.at<double>(i, j) = p_matrix1[i * 4 + j];
			project2.at<double>(i, j) = p_matrix2[i * 4 + j];
		}
	}

	for (int i = 0; i < 1; ++i) {
		points1.push_back(cv::Point2f(pos1.x(), pos1.y()));
		points2.push_back(cv::Point2f(pos2.x(), pos2.y()));
	}
	cv::Mat points4d;
	cv::triangulatePoints(project1, project2, points1, points2, points4d);

	world_coor[0] = points4d.at<float>(0, 0) / points4d.at<float>(3, 0);
	world_coor[1] = points4d.at<float>(1, 0) / points4d.at<float>(3, 0);
	world_coor[2] = points4d.at<float>(2, 0) / points4d.at<float>(3, 0);
}