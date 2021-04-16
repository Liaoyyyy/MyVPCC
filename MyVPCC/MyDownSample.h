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
pcl::PointCloud<pcl::PointXYZRGB>::Ptr myDownsamplePly(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointP, int model);
