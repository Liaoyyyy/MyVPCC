

#include <iostream>
#include "MyVpcc.h"
#include "myWritePly.h"
#include "MyDownSample.h"
#include "reducePoint.h"
#include "intPoint.h"
#include "enLargePoint.h"
#include "fillPoint.h"
int main()
{
    std::cout << "读取点云数据\n";
	//定义一个点云数据指针，接收读取到的点云数据。
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr originalPoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	//接收下采样数据
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr downSamplePoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr intDownSamplePoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr reducedownSamplePoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr enLargeP(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr filledPoint(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr filledPointReduce(new pcl::PointCloud<pcl::PointXYZRGB>());
	//读取点云数据
	originalPoint = myReadPly("original.ply");
	//对点云进行二分之一的坐标缩放并坐标取整
	downSamplePoint = myDownsamplePly(originalPoint, 1);
	//输出缩放坐标取整后的点云
	bool a = myWritePly(downSamplePoint, "downsampleOriginal.ply");
	//对坐标取整后的点云进行重坐标点的删减
	reducedownSamplePoint = reducePoint(downSamplePoint);
	//输出删减后的没有重复坐标的点云
	bool c = myWritePly(reducedownSamplePoint, "reducedDownsample.ply");
	//对缩小的点云进行原比例放大
	enLargeP = enLargePoint(reducedownSamplePoint);
	//打印输出放大后的下采样点云
	bool d = myWritePly(enLargeP,"upsampleReduced.ply");
	//对放大后的点云进行填充
	filledPoint = fillPoint(enLargeP);
	//对填充后的点云进行输出
	bool e = myWritePly(filledPoint, "filledUpsample.ply");
	//对填充后的点云进行重复点删除
	filledPointReduce = reducePoint(filledPoint);
	//对删除重复点的填充点云进行输出
	bool f = myWritePly(filledPointReduce, "filledRec.ply");
	return 0;
}

