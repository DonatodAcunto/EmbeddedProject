#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <io.h>
#include <windows.h>
#include <filesystem>
#include <Windows.h>

using namespace std;
using namespace cv;

// Function to return a list 
vector<string> get_all_files_names_within_folder(string folder);

int main()
{	
	// List of files
	vector<string> pictures_files;
	pictures_files = get_all_files_names_within_folder("C:/Users/docdo/Documents/GitHub/EmbeddedProject/Immagini Prova Ordinate");

	// Blob detection
	//--- To do for all the pictures
	Mat img = imread("PictureExample.jpg", IMREAD_GRAYSCALE);

	// Set up Default parameters for the detector
	SimpleBlobDetector detector;

	// Detecting blobs
	std::vector<KeyPoint> keypoints;
	detector.detect(img, keypoints);

	// Draw Circles on Blobs
	Mat im_with_keypoints;
	drawKeypoints(img, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Show blobs
	imshow("keypoints", im_with_keypoints);

	waitKey(0);
	return 0;
}

vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.jpg*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}
