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
pcl::PointCloud<pcl::PointXYZRGB>::Ptr enLargePoint(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointP);
