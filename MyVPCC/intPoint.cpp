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

//对缩小后的点云进行取整
pcl::PointCloud<pcl::PointXYZRGB>::Ptr intPoint(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointP) {
	//创建一个新点云对象，接收取整后的点云
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr intPoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	intPoint->resize((int)(pointP->width*pointP->height));
	for (int i = 0; i < (int)pointP->width*pointP->height; i++) {
		intPoint->points[i].x = ceil((pointP->points[i].x) / 2);
		intPoint->points[i].y = ceil((pointP->points[i].y) / 2);
		intPoint->points[i].z = ceil((pointP->points[i].z) / 2);
		intPoint->points[i].r = pointP->points[i].r;
		intPoint->points[i].rgb = pointP->points[i].rgb;
		intPoint->points[i].a = pointP->points[i].a;
	}
	return intPoint;
}