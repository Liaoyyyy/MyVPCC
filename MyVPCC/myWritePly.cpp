#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include<pcl/PCLPointCloud2.h>  
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/io/vtk_io.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <pcl/visualization/cloud_viewer.h> 
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/kdtree/kdtree_flann.h>

//���ply�����ļ��ĺ����������������Ƶ�ָ�� ����һ��bool���ͽ��
bool  myWritePly(pcl::PointCloud<pcl::PointXYZRGB>::Ptr writePoint,std::string writeName) {
	//����һ������ָ�룬������������ĵ�������
	//����һ�����ƶ������ڽ��մ��������ָ��
	pcl::PointCloud<pcl::PointXYZRGB> myPoint;
	pcl::PLYWriter writer;
	myPoint = *writePoint;
	writer.write(writeName, myPoint);

	std::cout << "������. -" << writeName <<"\n";
	return true;
}