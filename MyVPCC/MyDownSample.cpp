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

//该函数实现对点云的下采样，输入需要下采样的点云和采样模式，输出采样完成后的一个点云
pcl::PointCloud<pcl::PointXYZRGB>::Ptr myDownsamplePly(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointP,int model) {
	//定义一个点云指针，用来接收采样后的点云数据
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr sampledPointP(new pcl::PointCloud<pcl::PointXYZRGB>());
	switch (model)
	{
	case 1:
		sampledPointP->resize((int)pointP->width*pointP->height);
		for (int i = 0; i < pointP->width*pointP->height; i++) {
			sampledPointP->points[i].x = ceil((pointP->points[i].x) / 2);
			sampledPointP->points[i].y = ceil((pointP->points[i].y) / 2);
			sampledPointP->points[i].z = ceil((pointP->points[i].z) / 2);
			sampledPointP->points[i].rgb = pointP->points[i].rgb;
			sampledPointP->points[i].a = pointP->points[i].a;
		}

	default:
		break;
	}
	return sampledPointP;
}