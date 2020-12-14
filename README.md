# Zhangs-calibration
The project is aim to calibrate camera's intrinsic parameters, extrinsic parameters for both camera system, and reconstruction. It is supposed 
that chess board images from different angles has been got. 
The calibration functions are realized mainly by opencv 4.1.1. The code is wrote in C++ combined with QT. The used IDE is VS2017.
 ![image](https://github.com/liming467/Zhangs-calibration/blob/main/ui.png)
本软件采用张氏标定法结合棋盘格标定板进行双相机内、外参数计算，最后利用已经得到的左右相机图像匹配点坐标进行三维重建。假设已经得到了标定板处于不同姿态下的左右标定图片，并且已经得到了计算点在左右相机的图像匹配点坐标。
操作步骤主要分为三个部分：
## （1）	内参标定
鼠标点击Image file按钮，将会弹出一个对话框，选择所有参与标定内参的棋盘格图片。选择完标定图片，右边的输入框将会显示第一个图片的路径及图片张数，之后点击计算。程序将会在图片路径在新建一个Result_××的文件夹，生成的相机内参文件_intrinsicParameters.txt和以图片为名的标定板角点坐标文件将会保存在此新建的文件夹下，后续步骤将会用到。
注意：要对左右相机的标定图片分别执行此内参标定操作。
 ![image](https://github.com/liming467/Zhangs-calibration/blob/main/camera%20image.png)
 标定图片
## （2）	外参标定
点击Coner files按钮后，选择内参标定步骤计算生成的角点坐标文件，选择后将会显示第一个文件的路径。Intrinsic file按钮选择内参标定步骤计算生成的相机内参文件。savePath按钮选择相机外参数据(双相机间的旋转矩阵+平移向量)保存的路径及文件名，输入框内将显示其路径。之后，点击计算按钮，除了会按照指定保存文件名保存外参数据，还会在与外参文件同路径在生成文件_projectionMatrix.txt，其中有基础矩阵和左、右投影矩阵。
## （3）	三维重建
分别选择左右相机的计算点图像坐标文件，并选择步骤（3）生成的投影矩阵文件，点击计算即在投影矩阵所在目录下生成三维坐标文件Coordinates_3d.txt和相对于第一张图片的三维位移文件Displacement_3d.txt。

