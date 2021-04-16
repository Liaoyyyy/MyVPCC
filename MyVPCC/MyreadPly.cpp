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

//读取ply点云文件的函数，输入点云文件的位置 返回一个点云类型的指针
pcl::PointCloud<pcl::PointXYZRGB>::Ptr myReadPly(std::string fileName) {
	//定义一个点云指针，用来接收载入的点云数据
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr plyPoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::io::loadPLYFile(fileName, *plyPoint);
	std::cout << "加载完成...\n" << "点数：" << plyPoint->width*plyPoint->height << std::endl;
	return plyPoint;
}
