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

//���ظ������ɾ���ĺ����������ɾ���ĵ��ƶ���ָ���ɾ��ģʽ
pcl::PointCloud<pcl::PointXYZRGB>::Ptr reducePoint(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointP) {
	//����һ�����ƶ������ڽ���ɾ����ĵ���
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr reduceCloudPtr(new pcl::PointCloud<pcl::PointXYZRGB>());
	//����KD��
	pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree;
	std::cout << "����KD��...\n";
	kdtree.setInputCloud(pointP);

	std::cout << "�������.\n";
	//�������,��¼ɾ���ĵ�
	std::set<int> reduceIndex;
	std::set<int> originalIndex;
	std::set<int> difIndex;
	double radius = 16;
	//����һ��������¼����������������ĵ�
	//��ȡĿ���
	std::cout << "��ȡ�ظ���......\n";
	for (int i = 0; i < (int)(pointP->width*pointP->height); i++) {
		originalIndex.insert(i);
		std::vector<int> ind(16);
		std::vector<float> dist(16);
		//��ʼ��һ����ѯ��
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
	//��������ԭʼ���ƺ�ɾ������֮��Ĳ���,Ҳ���ǵõ������ĵ������
	std::set_difference(
		originalIndex.begin(), originalIndex.end(),
		reduceIndex.begin(), reduceIndex.end(),
		std::insert_iterator<std::set<int>>(difIndex, difIndex.begin())
	);
	std::cout << "��ȡ���." << endl;

	//����һ���µĵ��ƶ���,�����ظ���ӽ�ȥ,�Դ��Ƴ�û���ظ���ĵ������ݼ�,�������.
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