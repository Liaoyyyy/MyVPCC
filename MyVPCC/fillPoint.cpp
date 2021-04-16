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

//对点云进行填充
pcl::PointCloud<pcl::PointXYZRGB>::Ptr fillPoint(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointP) {
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr filledPoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree;
	kdtree.setInputCloud(pointP);
	//创建一个容器用来标记点是否被遍历过
	std::vector<bool> havePoint(pointP->width*pointP->height, true);
	for (int i = 0; i < pointP->width*pointP->height; i++) {
		filledPoint->push_back(pointP->points[i]);
		if (havePoint[i] == false) {
			continue;
		}
		else {
			havePoint[i] = false;
			std::vector<int> index(16);
			std::vector<float> distance(16);
			int k = 16;
			pcl::PointXYZRGB point2 = pointP->points[i];
			int haveNN = kdtree.nearestKSearch(point2, k, index, distance);
			for (int j = 1; j < 16; j++) {
				if (distance[j] > 1 && distance[j] <= 10)
				{
					pcl::PointXYZRGB point3;
					point3.x = (pointP->points[i].x + pointP->points[index[j]].x)*0.5;
					point3.y = (pointP->points[i].y + pointP->points[index[j]].y)*0.5;
					point3.z = (pointP->points[i].z + pointP->points[index[j]].z)*0.5;
					point3.r = (pointP->points[i].r + pointP->points[index[j]].r)*0.5;
					point3.g = (pointP->points[i].g + pointP->points[index[j]].g)*0.5;
					point3.b = (pointP->points[i].b + pointP->points[index[j]].b)*0.5;
					filledPoint->push_back(point3);
				}
			}
		}
	}
	return filledPoint;
}