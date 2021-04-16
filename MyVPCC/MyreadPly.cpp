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

//��ȡply�����ļ��ĺ�������������ļ���λ�� ����һ���������͵�ָ��
pcl::PointCloud<pcl::PointXYZRGB>::Ptr myReadPly(std::string fileName) {
	//����һ������ָ�룬������������ĵ�������
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr plyPoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::io::loadPLYFile(fileName, *plyPoint);
	std::cout << "�������...\n" << "������" << plyPoint->width*plyPoint->height << std::endl;
	return plyPoint;
}
