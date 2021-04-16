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

//该函数实现点云的放大
pcl::PointCloud<pcl::PointXYZRGB>::Ptr enLargePoint(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointP) {
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr largePoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	largePoint->resize((int)pointP->width*pointP->height);
	for (int i = 0; i < pointP->width*pointP->height; i++) {
		largePoint->points[i].x = (pointP->points[i].x) * 2;
		largePoint->points[i].y = (pointP->points[i].y) * 2;
		largePoint->points[i].z = (pointP->points[i].z) * 2;
		largePoint->points[i].rgb = pointP->points[i].rgb;
		largePoint->points[i].a = pointP->points[i].a;
	}
	return largePoint;
}