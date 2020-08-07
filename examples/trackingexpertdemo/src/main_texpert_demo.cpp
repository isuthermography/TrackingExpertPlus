// stl
#include <iostream>
#include <string>
#include <vector>

// local
#include "ArgParser.h"
#include "TrackingExpertDemo.h"
#include "TrackingExpertParams.h"
using namespace texpert;


TEParams populateParams(Arguments params)
{
	TEParams p;

	p.angle_step = params.fd_angle_step;
	p.camera_sampling_offset = 8;
	p.cluster_rot_threshold = params.fd_cluster_rot_th;
	p.cluster_trans_threshold = params.fd_cluster_trans_th;
	p.curvature_search_radius = params.fd_curvature_radius;
	p.icp_num_max_iterations = params.icp_max_iterations;
	p.icp_outlier_reject_angle = params.icp_outlier_ang_th;
	p.icp_outlier_reject_distance = params.icp_outlier_dist_th;
	p.icp_termination_dist = params.icp_min_rms;
	p.sampling_grid_size = params.sampling_grid_size;
	p.verbose = params.verbose;

	return p;
}


void displayKeyboard(void) {

	std::cout << "\nKeyboard layout:\n--------------------------------------------------------------------------" << std::endl;

	std::cout << " 1\tDisplay matching curvatures per point." << std::endl;
	std::cout << " 2\tDisplay matching curvatures patches per point." << std::endl;
	std::cout << " q\tMove to the next matching point." << std::endl;
	std::cout << " w\tMove to the previous matching point." << std::endl;
	std::cout << " 3\tDisplay pose clusters." << std::endl;
	std::cout << " a\tMove to the next pose cluster." << std::endl;
	std::cout << " s\tMove to the previous pose cluster." << std::endl;
	std::cout << " 4\tDisplay curvature histogram values." << std::endl;

	std::cout << "\n--------------------------------------------------------------------------" << std::endl;
}

// -scene ../data/test/Azure_Kinect_model_1_test.ply -model ../data/stanford_bunny_pc.obj -verbose
// -cam AzureKinect -model ../data/stanford_bunny_pc.obj -verbose

int main(int argc, char** argv) {

	std::cout << "TrackingExpertPlusDemo" << std::endl;
	std::cout << "V0.5-20200803, Aug. 2020\n" << std::endl;
	std::cout << "--------------------------------------------------------------------------" << std::endl;
	std::cout << "The demo demonstrates the use of TrackingExpert+" << std::endl;
	std::cout << "It was prepared to track one object given a 3D point cloud model as input.\n" << std::endl;

	std::cout << "Rafael Radkowski" << std::endl;
	std::cout << "Iowa State University" << std::endl;
	std::cout << "rafael@iastate.edu" << std::endl;
	std::cout << "MIT License" << std::endl;
	std::cout << "--------------------------------------------------------------------------\n" << std::endl;

	displayKeyboard(); 

	// parse the command line arguments
	Arguments params = ArgParser::Parse(argc, argv);

	CaptureDeviceType type = CaptureDeviceType::None;
	if (params.camera_type.compare("AzureKinect") == 0) type = KinectAzure;

	
	// Start the demo
	TrackingExpertDemo* demo = new TrackingExpertDemo();
	demo->setParams(populateParams( params));
	demo->setVerbose(params.verbose);
	demo->setCamera(type); 
	demo->loadScene(params.scene_file); // ignored when a camera is set.
	demo->loadModel(params.model_file, "model");

	demo->run();

	delete demo;

	return 1;
}