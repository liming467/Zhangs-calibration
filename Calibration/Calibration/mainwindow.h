#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QLabel>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/video.hpp>

#include <iostream>
#include <fstream>;
#include <ostream>;

using namespace cv;
using namespace std;

typedef struct {
	double x = 0;
	double y = 0;
	double z = 0;
}Point_3d;


class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = Q_NULLPTR);

	

private:
    Ui::MainWindowClass ui;

	/*************************************slot function*****************************************/
	//内参标定
	void ptn_imageFile_clicked();		
	void ptn_internalCal_clicked();

	//外参标定
	void ptn_leftCorners_clicked();
	void ptn_leftIntrinsic_clicked();
	void ptn_rightCorners_clicked();
	void ptn_rightIntrinsic_clicked();
	void ptn_savePath_clicked();
	void ptn_externalCal_clicked();

	//三维重建
	void ptn_leftCoords_clicked();
	void ptn_rightCoords_clicked();
	void ptn_projectionFile_clicked();
	void ptn_reconstuctionCal_clicked();	
	

	QString getPath_noSuffix(QString path);
	QString creatNewPath(QString path);

	void updateChessboardParameters();

	void saveCornerData(QString filePath, QString savePath, const vector<Point2f> &corners);
	void saveIntrinsicParameters(QString savePath, const Mat &intrinsicMatrix, const Mat &distortionCoeffs);
	void saveExtrinsicParameters(QString savePath, const Mat &R, const Mat &T);
	void saveProjectionMatrix(QString savePath, const Mat &Fundamental, const Mat &leftCameraMatrix, const Mat &rightCameraMatrix, const Mat &R, const Mat &T);
	void save3dPointsInfo(QString savePath, const QVector<Point_3d> &points);

	//利用左右相机图像匹配坐标和两个投影矩阵进行三维重建
	void reconstruction(const QPointF &pos1, const QPointF &pos2, const QVector<double> &p_matrix1, const QVector<double> &p_matrix2, QVector<double> &world_coor);



	void getCameraMatrix(QString path, Mat &cameraMatrix, Mat &distortionCoeff);
	QVector<QPointF> getCornerCoordinates(QString path);
	void getProjectionMatrix(QString path, QVector<double> &mainProjection, QVector<double> &assistProjection);

	QVector<QVector<double>> matrix_multiply(const QVector<QVector<double>> &matrix1, const QVector<QVector<double>> &matrix2);

	QVector<QPointF> readDataFromFile(int skipNumber, QString path);

	inline Mat getRotationVector(Mat R) {
		Mat temp;
		Rodrigues(R, temp);
		return temp;
	}



	//内参
	QStringList     m_imageFileList;
	QString         m_internalSavePath = "";
	//外参
	QStringList     m_leftCornerPath;
	QStringList     m_rightCornerPath;	
	QString         m_leftIntrinsicPath;
	QString         m_rightIntrinsicPath;
	QString         m_externalSavePath = "";
	//三维重建
	QString         m_leftCoordPath = "";
	QString         m_rightCoordPath = "";
	QString         m_projectionFilePath = "";

	int             m_widthPointNumber = 12;
	int             m_heightPointNumber = 9;
	int             m_chessboardSize = 16;
	int             m_imgWidth = 0;
	int             m_imgHeight = 0;	
	QLabel*         m_statusLabel = nullptr;
};
