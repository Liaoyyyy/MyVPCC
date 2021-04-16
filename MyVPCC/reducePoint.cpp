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

//对重复点进行删减的函数，输入待删减的点云对象指针和删减模式
pcl::PointCloud<pcl::PointXYZRGB>::Ptr reducePoint(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointP) {
	//创建一个点云对象用于接收删减后的点云
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr reduceCloudPtr(new pcl::PointCloud<pcl::PointXYZRGB>());
	//构建KD树
	pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree;
	std::cout << "构建KD树...\n";
	kdtree.setInputCloud(pointP);

	std::cout << "构建完成.\n";
	//创建标记,记录删减的点
	std::set<int> reduceIndex;
	std::set<int> originalIndex;
	std::set<int> difIndex;
	double radius = 16;
	//定义一个容器记录搜索到的最近点距离的点
	//获取目标点
	std::cout << "获取重复点......\n";
	for (int i = 0; i < (int)(pointP->width*pointP->height); i++) {
		originalIndex.insert(i);
		std::vector<int> ind(16);
		std::vector<float> dist(16);
		//初始化一个查询点
		pcl::PointXYZRGB point = pointP->points[i];
		int size = kdtree.nearestKSearch(point, radius, ind, dist);
		if (size > 0) {
			for (int j = 0; j < ind.size(); j++) {
				if ((ind[j] != i) && (dist[j] <= 0.0000001) && (ind[j] > i)) {
					if (reduceIndex.find(ind[j]) == reduceIndex.end()) {
						reduceIndex.insert(ind[j]);
					}
					else
					{
						reduceIndex.insert(i);
					}
				}
			}
		}
		else {
			continue;
		}
	}
	//这里计算出原始点云和删除点云之间的并集,也就是得到保留的点云序号
	std::set_difference(
		originalIndex.begin(), originalIndex.end(),
		reduceIndex.begin(), reduceIndex.end(),
		std::insert_iterator<std::set<int>>(difIndex, difIndex.begin())
	);
	std::cout << "获取完成." << endl;

	//创建一个新的点云对象,将非重复点加进去,以此制成没有重复点的点云数据集,完成缩放.
	int count = (int)(pointP->width*pointP->height) - (int)(reduceIndex.size());
	reduceCloudPtr->resize(count);
	int s = 0;
	for (int p = 0; p < (int)pointP->width*pointP->height; p++) {
		if (reduceIndex.find(p) == reduceIndex.end()) {
			reduceCloudPtr->points[s].x = pointP->points[p].x;
			reduceCloudPtr->points[s].y = pointP->points[p].y;
			reduceCloudPtr->points[s].z = pointP->points[p].z;
			reduceCloudPtr->points[s].rgb = pointP->points[p].rgb;
			reduceCloudPtr->points[s].a = pointP->points[p].a;
			s++;
		}
	}
	return reduceCloudPtr;	
}