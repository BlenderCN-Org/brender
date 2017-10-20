#pragma once

#ifndef OBJEXPORTMANAGER_H
#define OBJEXPORTMANAGER_H

#include <fstream>
#include <chrono>
#include <vector>
#include <memory>
#include <string>
#include <iostream>

namespace Brender {

	class ObjExportable;

	class ObjExportManager {
	public:
		static ObjExportManager* getInstance();
		int getFrame();
		void exportObjs(); //does not use timestamp
		void exportObjs(double time);
		void add(std::shared_ptr<ObjExportable> exportable);
		~ObjExportManager()
		{
			instanceFlag = false;
		}
	private:
		static bool instanceFlag;
		static ObjExportManager *manager;
		int frame;
		std::vector<std::shared_ptr<ObjExportable>> objexportables;
		ObjExportManager()
		{
			//private constructor
			frame = 0;
		}
	}
	bool ObjExportManager::instanceFlag = false;
	ObjExportManager* ObjExportManager::manager = NULL;

	ObjExportManager* ObjExportManager::getInstance()
	{
		if (!instanceFlag)
		{
			manager = new ObjExportManager();
			//manager = make_shared<ObjExportManager>();
			instanceFlag = true;
			return manager;
		}
		else
		{
			return manager;
		}
	}

	int ObjExportManager::getFrame()
	{
		return frame;
	}

	void ObjExportManager::exportObjs()
	{	
		int objNum = 1;
		for (auto objExportable : objExportables) {
			ofstream outfile;
			
			char filename[50];
			const char* checkname = objExportable->getObjName().c_str();
			//if object has not been given name
			if (strcmp(checkname, "") == 0) {
				sprintf(filename, "../resources/testfolder3/%06d_Object%d.obj", frame, objNum);
			}
			//if object has been given specific name
			else {
				std::string objname_str = objExportable->getObjName();
				char* objname_char = new char[objname_str.length() + 1];
				strcpy(objname_char, objname_str.c_str());
				sprintf(filename, "../resources/testfolder3/%06d_%s.obj", frame, objname_char);
			}
			//open file
			outfile.open(filename);
			//frame string
			char framestring[50];
			sprintf(framestring, "# frame %06d \n", frame);
			outfile << framestring;
			//obj name
			//if object has not been given name
			if (strcmp(checkname, "") == 0) {
				outfile << "# name Object" + to_string(objNum) + " \n";
			}
			//if object has been given specific name
			else {
				outfile << "# name " + objExportable->getObjName() + " \n";
			}
			objExportable->exportObj(outfile);
			outfile.close();
			objNum++;
		}
		//Only time frame should be changed/modified
		frame++;
	}

	void ObjExportManager::exportObjs(double time)
	{
		int objNum = 1;
		for (auto objExportable : objExportables) {
			ofstream outfile;

			char filename[100];
			
			const char* checkname = objExportable->getObjName().c_str();
			//if object has not been given name
			if (strcmp(checkname, "") == 0 ){	
				sprintf(filename, "../resources/testfolder3/%06d_Object%d.obj", frame, objNum);
			}
			//if object has been given specific name
			else {
				std::string objname_str = objExportable->getObjName();
				char* objname_char = new char[objname_str.length() + 1];
				strcpy(objname_char, objname_str.c_str());
				sprintf(filename, "../resources/testfolder3/%06d_%s.obj", frame, objname_char);
			}
			//open file
			outfile.open(filename);
			//frame string
			char framestring[50];
			sprintf(framestring, "# frame %06d \n", frame);
			outfile << framestring;
			//frame time
			char timeval[50];
			sprintf(timeval, "# time %f \n", time);
			outfile << timeval;
			//obj name
			//if object has not been given name
			if (strcmp(checkname, "") == 0) {
				outfile << "# name Object" + to_string(objNum) + " \n";
			}
			//if object has been given specific name
			else {
				outfile << "# name " + objExportable->getObjName() + " \n";
			}
			objExportable->exportObj(outfile);
			outfile.close();
			objNum++;
		}
		//Only time frame should be changed/modified
		frame++;
	}

	void ObjExportManager::add(shared_ptr<ObjExportable> exportable)
	{
		objExportables.push_back(exportable);
	}

}

#endif	// OBJEXPORTABLE_H