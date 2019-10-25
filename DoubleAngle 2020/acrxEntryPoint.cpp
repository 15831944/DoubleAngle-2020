// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("DYNA")

struct Profil
{
	std::string section;
	double h;
	double b;
	double tf;
	double r1;
	double r2;
	double e;
};

Profil pro[] =
{
	{ "2L50",  50,  50,  5,  7,  3.5, 14},
	{ "2L60",  60,  60,  6,  8,  4,   16.9},
	{ "2L70",  70,  70,  7,  9,  4.5, 19.7},
	{ "2L80",  80,  80,  8,  10, 5,   22.6},
	{ "2L90",  90,  90,  9,  11, 5.5, 25.4},
	{ "2L100", 100, 100, 10, 12, 6,   28.2},
	{ "2L110", 110, 110, 12, 13, 6.5, 31.5},
	{ "2L120", 120, 120, 12, 13, 6.5, 34},
};

struct NProfil
{
	std::string section;
	double h;
	double b;
	double tw;
	double tf;
	double r1;
	double r2;
};

NProfil npro[] =
{
	{ "2NPU80",  80,  45,  6,    8,    8,    4},
	{ "2NPU100", 100, 50,  6,    8.5,  8.5,  4.5},
	{ "2NPU120", 120, 55,  7,    9,    9,    4.5},
	{ "2NPU140", 140, 60,  7,    10,   10,   5},
	{ "2NPU160", 160, 65,  7.5,  10.5, 10.5, 5.5},
	{ "2NPU180", 180, 70,  8,    11,   11,   5.5},
	{ "2NPU200", 200, 75,  8.5,  11.5, 11.5, 6},
	{ "2NPU220", 220, 80,  9,    12.5, 12.5, 6.5},
	{ "2NPU240", 240, 85,  9.5,  13,   13,   6.5},
	{ "2NPU260", 260, 90,  10,   14,   14,   7},
	{ "2NPU280", 280, 95,  10,   15,   15,   7.5},
	{ "2NPU300", 300, 100, 10,   16,   16,   8},
	{ "2NPU320", 320, 100, 14,   17.5, 17.5, 8.75},
	{ "2NPU350", 350, 100, 14,   16,   16,   8},
	{ "2NPU380", 380, 102, 13.5, 16,   16,   8},
	{ "2NPU400", 400, 110, 14,   18,   18,   9},
};

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CDoubleAngle2020App : public AcRxArxApp {

public:
	CDoubleAngle2020App () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CDoubleAngle2020App class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	static void createLinetype()
	{
		AcDbLinetypeTable *pLtypeTable = NULL;
		// Get the linetype table from the drawing
		if (acdbHostApplicationServices()->workingDatabase()->
			getLinetypeTable(pLtypeTable, AcDb::kForWrite) == Acad::eOk)
		{
			AcDbLinetypeTableRecord *pLtypeTableRecord = new AcDbLinetypeTableRecord;
			// Set all of the properties of the linetype table record
			pLtypeTableRecord->setAsciiDescription(ACRX_T("T E S T -"));
			pLtypeTableRecord->setPatternLength(0.75);
			pLtypeTableRecord->setNumDashes(2);
			pLtypeTableRecord->setDashLengthAt(0, 0.5);
			pLtypeTableRecord->setDashLengthAt(1, -0.25);
			pLtypeTableRecord->setName(ACRX_T("T_E_S_T"));
			AcDbObjectId tmpId;

			// Add the new linetype to the linetype table
			if (pLtypeTable->add(tmpId, pLtypeTableRecord) == Acad::eOk)
			{
				pLtypeTableRecord->close();
				acutPrintf(ACRX_T("\nNew linetype successfully created."));
			}
			else
			{
				delete pLtypeTableRecord;
				acutPrintf(ACRX_T("\nCannot add new linetype to the drawing."));
			}
			pLtypeTable->close();
		}
	}

	static void DrawAnglePlanView(const Profil& profil, const double& scale)
	{
		AcDbDatabase *pCurDb;
		AcDbBlockTable *pBlkTable;
		AcDbBlockTableRecord *pBlkTableRecord;

		//Adesk::Boolean firstPick = Adesk::kTrue;

		// Polylines are created in terms of the
		// Entity Coordinate System as opposed to
		// the World Coordinate System. If we are
		// using a UCS other than WCS we need to
		// translate back to the ECS.

		AcGeMatrix3d ucsMat;
		AcGeMatrix2d ucsMat2d;

		acdbUcsMatrix(ucsMat);
		ucsMat2d(0, 0) = ucsMat(0, 0);
		ucsMat2d(0, 1) = ucsMat(0, 1);
		ucsMat2d(0, 2) = ucsMat(0, 3);
		ucsMat2d(1, 0) = ucsMat(1, 0);
		ucsMat2d(1, 1) = ucsMat(1, 1);
		ucsMat2d(1, 2) = ucsMat(1, 3);

		Adesk::Boolean keepPicking = Adesk::kTrue;
		Adesk::Boolean hasSymmetry = Adesk::kTrue;

		while (keepPicking)
		{
			AcDbPolyline *pPolyEnt;

			AcDbObjectId polyId;

			AcGePoint2d pkPt;
			AcGePoint2dArray arPts;
			ads_point pick;

			int retCode;
			int numPts;

			retCode = acedGetPoint(NULL, L"\nPick DAngle center point: ", pick);

			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}

			pkPt.x = pick[X];
			pkPt.y = pick[Y];

			arPts.removeAll();

			// Append the picked point to the AcGePoint2dArray
			arPts.append(pkPt);
			arPts.append(AcGePoint2d(pkPt.x + scale * profil.b / 2, pkPt.y));
			arPts.append(AcGePoint2d(pkPt.x + scale * profil.b, pkPt.y));
			arPts.append(AcGePoint2d(pkPt.x + scale * profil.b, pkPt.y + scale * profil.tf - scale * profil.r2));
			arPts.append(AcGePoint2d(pkPt.x + scale * profil.b - scale * profil.r2, pkPt.y + scale * profil.tf));
			arPts.append(AcGePoint2d(pkPt.x + scale * profil.tf + scale * profil.r1, pkPt.y + scale * profil.tf));
			arPts.append(AcGePoint2d(pkPt.x + scale * profil.tf, pkPt.y + scale * profil.tf + scale * profil.r1));
			arPts.append(AcGePoint2d(pkPt.x + scale * profil.tf, pkPt.y + scale * profil.h - scale * profil.r2));
			arPts.append(AcGePoint2d(pkPt.x + scale * profil.tf - scale * profil.r2, pkPt.y + scale * profil.h));
			arPts.append(AcGePoint2d(pkPt.x, pkPt.y + scale * profil.h));
			arPts.append(AcGePoint2d(pkPt.x, pkPt.y + scale * profil.h / 2));

			numPts = arPts.length();

			pCurDb = acdbHostApplicationServices()->workingDatabase();
			// Get the model space Block Table Record
			pCurDb->getBlockTable(pBlkTable, AcDb::kForRead);
			pBlkTable->getAt(ACDB_MODEL_SPACE, pBlkTableRecord, AcDb::kForWrite);
			pBlkTable->close();

			pPolyEnt = new AcDbPolyline(numPts);

			// Process the AcGePoint2dArray and add verticies to
			// our polyline.
			for (int idx = 0; idx < numPts; idx++)
			{
				pkPt = arPts.at(idx);
				pkPt.transformBy(ucsMat2d);
				pPolyEnt->addVertexAt(idx, pkPt);
			}

			const double pi = std::acos(-1);

			pPolyEnt->setBulgeAt(0, 0);
			pPolyEnt->setBulgeAt(1, 0);
			pPolyEnt->setBulgeAt(2, 0);
			pPolyEnt->setBulgeAt(3, std::tan(pi / 8));
			pPolyEnt->setBulgeAt(4, 0);
			pPolyEnt->setBulgeAt(5, std::tan(-pi / 8));
			pPolyEnt->setBulgeAt(6, 0);
			pPolyEnt->setBulgeAt(7, std::tan(pi / 8));
			pPolyEnt->setBulgeAt(8, 0);
			pPolyEnt->setBulgeAt(9, 0);
			pPolyEnt->setBulgeAt(10, 0);

			pPolyEnt->setClosed(Adesk::kTrue);

			//// scale the pEnt
			//AcGeMatrix3d matScale = AcGeMatrix3d::scaling(scale, AcGePoint3d(pkPt.x, pkPt.y, 0));
			//pPolyEnt->transformBy(matScale);

			if (hasSymmetry)
			{
				//move the polyline from symtery axis to real point
				AcGeMatrix3d m;
				AcGeVector3d v(5 * scale, 0, 0); // X, Y, Z translation
				m.setTranslation(v);
				pPolyEnt->transformBy(m);

				// Create a copy of the original polyline
				AcDbPolyline *pPolyEntMir = static_cast<AcDbPolyline*>(pPolyEnt->clone());

				//mirror the polyline across the symetry axis
				AcGeLine3d acGeLine3D(AcGePoint3d(pkPt.x, pkPt.y, 0), AcGePoint3d(pkPt.x, pkPt.y + profil.h, 0));
				AcGeMatrix3d mir;
				mir.setToMirroring(acGeLine3D);
				pPolyEntMir->transformBy(mir);

				//// scale the pEntmir
				//AcGeMatrix3d matScale = AcGeMatrix3d::scaling(scale, AcGePoint3d(pkPt.x, pkPt.y, 0));
				//pPolyEntMir->transformBy(matScale);

				AcDbObjectId polyMirId;
				pBlkTableRecord->appendAcDbEntity(polyMirId, pPolyEntMir);
				pPolyEntMir->close();
			}

			// Add the AcDbPolyline entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(polyId, pPolyEnt);

			pBlkTableRecord->close();
			pPolyEnt->close();
		}// while
	}

	static void DrawAngleSectionView(const Profil& profil, const double& scale)
	{
		AcDbDatabase *pCurDb;
		AcDbBlockTable *pBlkTable;
		AcDbBlockTableRecord *pBlkTableRecord;

		//Adesk::Boolean firstPick = Adesk::kTrue;

		// Polylines are created in terms of the
		// Entity Coordinate System as opposed to
		// the World Coordinate System. If we are
		// using a UCS other than WCS we need to
		// translate back to the ECS.

		AcGeMatrix3d ucsMat;
		AcGeMatrix2d ucsMat2d;

		acdbUcsMatrix(ucsMat);
		ucsMat2d(0, 0) = ucsMat(0, 0);
		ucsMat2d(0, 1) = ucsMat(0, 1);
		ucsMat2d(0, 2) = ucsMat(0, 3);
		ucsMat2d(1, 0) = ucsMat(1, 0);
		ucsMat2d(1, 1) = ucsMat(1, 1);
		ucsMat2d(1, 2) = ucsMat(1, 3);

		Adesk::Boolean keepPicking = Adesk::kTrue;
		const double pi = std::acos(-1);

		while (keepPicking)
		{
			AcDbPolyline *pPolyEnt;
			AcDbObjectId polyId;

			AcDbLine *pLineEnt;
			AcDbObjectId lineId;

			AcGePoint2d sp, ep, pkPt;
			AcGePoint3d spL, epL;
			AcGePoint2dArray arPts;
			ads_point pick, secondPick;

			int retCode;
			int numPts;

			retCode = acedGetPoint(NULL, L"\nPick DAngle start point: ", pick);
			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}
			retCode = acedGetPoint(pick, L"\nPick DAngle end point: ", secondPick);
			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}

			sp.x = pick[X];
			sp.y = pick[Y];

			ep.x = secondPick[X];
			ep.y = secondPick[Y];

			double dblAngle = acutAngle(reinterpret_cast<double*>((ads_point*)(&sp)),
				reinterpret_cast<double*>((ads_point*)(&ep)));
			double dbl90Deg = 90 * pi / 180;

			double h, tf, e;
			h = scale * profil.h;
			//b = scale * profil.b;
			tf = scale * profil.tf;
			e = scale * profil.e;

			spL.x = sp.x + (e - tf) * sin(dblAngle);
			spL.y = sp.y - (e - tf) * sin(dbl90Deg - dblAngle);
			spL.z = 0;
			epL.x = ep.x + (e - tf) * sin(dblAngle);
			epL.y = ep.y - (e - tf) * sin(dbl90Deg - dblAngle);
			epL.z = 0;

			// Create the line entity
			pLineEnt = new AcDbLine(spL, epL);

			arPts.removeAll();

			// Append the sideview rectangle corner points to the AcGePoint2dArray
			arPts.append(AcGePoint2d(sp.x - (h - e)*sin(dblAngle), sp.y + (h - e)*sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(ep.x - (h - e)*sin(dblAngle), ep.y + (h - e)*sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(ep.x + (e)*sin(dblAngle), ep.y - (e)*sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(sp.x + (e)*sin(dblAngle), sp.y - (e)*sin(dbl90Deg - dblAngle)));

			numPts = arPts.length();

			pCurDb = acdbHostApplicationServices()->workingDatabase();
			// Get the model space Block Table Record
			pCurDb->getBlockTable(pBlkTable, AcDb::kForRead);
			pBlkTable->getAt(ACDB_MODEL_SPACE, pBlkTableRecord, AcDb::kForWrite);
			pBlkTable->close();

			pPolyEnt = new AcDbPolyline(numPts);

			// Process the AcGePoint2dArray and add verticies to
			// our polyline.
			for (int idx = 0; idx < numPts; idx++)
			{
				pkPt = arPts.at(idx);
				pkPt.transformBy(ucsMat2d);
				pPolyEnt->addVertexAt(idx, pkPt);
			}

			pPolyEnt->setClosed(Adesk::kTrue);

			// Add the AcDbLine entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(lineId, pLineEnt);

			// Add the AcDbPolyline entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(polyId, pPolyEnt);

			pBlkTableRecord->close();
			pLineEnt->close();
			pPolyEnt->close();
		}
	}

	static void DrawAngleTopView(const Profil& profil, const double& scale)
	{
		AcDbDatabase *pCurDb;
		AcDbBlockTable *pBlkTable;
		AcDbBlockTableRecord *pBlkTableRecord;

		//Adesk::Boolean firstPick = Adesk::kTrue;

		// Polylines are created in terms of the
		// Entity Coordinate System as opposed to
		// the World Coordinate System. If we are
		// using a UCS other than WCS we need to
		// translate back to the ECS.

		AcGeMatrix3d ucsMat;
		AcGeMatrix2d ucsMat2d;

		acdbUcsMatrix(ucsMat);
		ucsMat2d(0, 0) = ucsMat(0, 0);
		ucsMat2d(0, 1) = ucsMat(0, 1);
		ucsMat2d(0, 2) = ucsMat(0, 3);
		ucsMat2d(1, 0) = ucsMat(1, 0);
		ucsMat2d(1, 1) = ucsMat(1, 1);
		ucsMat2d(1, 2) = ucsMat(1, 3);

		Adesk::Boolean keepPicking = Adesk::kTrue;
		Adesk::Boolean hasSymmetry = Adesk::kTrue;
		const double pi = std::acos(-1);

		while (keepPicking)
		{
			AcDbPolyline *pPolyEnt;
			AcDbObjectId polyId;

			AcDbLine *pLineEnt;
			AcDbObjectId lineId;

			AcGePoint2d sp, ep, pkPt;
			AcGePoint3d spL, epL;
			AcGePoint2dArray arPts;
			ads_point pick, secondPick;

			int retCode;
			int numPts;

			retCode = acedGetPoint(NULL, L"\nPick DAngle start point: ", pick);
			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}
			retCode = acedGetPoint(pick, L"\nPick DAngle end point: ", secondPick);
			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}

			sp.x = pick[X];
			sp.y = pick[Y];

			ep.x = secondPick[X];
			ep.y = secondPick[Y];

			double dblAngle = acutAngle(reinterpret_cast<double*>((ads_point*)(&sp)),
				reinterpret_cast<double*>((ads_point*)(&ep)));
			double dbl90Deg = 90 * pi / 180;

			double h, tf, e, dis;
			h = scale * profil.h;
			//b = scale * profil.b;
			tf = scale * profil.tf;
			e = scale * profil.e;
			dis = scale * 5;

			spL.x = sp.x + (dis + tf) * sin(dblAngle);
			spL.y = sp.y - (dis + tf) * sin(dbl90Deg - dblAngle);
			spL.z = 0;
			epL.x = ep.x + (dis + tf) * sin(dblAngle);
			epL.y = ep.y - (dis + tf) * sin(dbl90Deg - dblAngle);
			epL.z = 0;

			// Create the line entity
			pLineEnt = new AcDbLine(spL, epL);

			arPts.removeAll();

			// Append the sideview rectangle corner points to the AcGePoint2dArray
			arPts.append(AcGePoint2d(sp.x + dis * sin(dblAngle), sp.y - dis * sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(ep.x + dis * sin(dblAngle), ep.y - dis * sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(ep.x + (dis + h)*sin(dblAngle), ep.y - (dis + h)*sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(sp.x + (dis + h)*sin(dblAngle), sp.y - (dis + h)*sin(dbl90Deg - dblAngle)));

			numPts = arPts.length();

			pCurDb = acdbHostApplicationServices()->workingDatabase();
			// Get the model space Block Table Record
			pCurDb->getBlockTable(pBlkTable, AcDb::kForRead);
			pBlkTable->getAt(ACDB_MODEL_SPACE, pBlkTableRecord, AcDb::kForWrite);
			pBlkTable->close();

			pPolyEnt = new AcDbPolyline(numPts);

			// Process the AcGePoint2dArray and add verticies to
			// our polyline.
			for (int idx = 0; idx < numPts; idx++)
			{
				pkPt = arPts.at(idx);
				pkPt.transformBy(ucsMat2d);
				pPolyEnt->addVertexAt(idx, pkPt);
			}

			pPolyEnt->setClosed(Adesk::kTrue);

			if (hasSymmetry)
			{
				// Create a copy of the original polyline
				AcDbPolyline *pPolyEntMir = static_cast<AcDbPolyline*>(pPolyEnt->clone());
				// Create a copy of the original line
				AcDbLine *pLineEntMir = static_cast<AcDbLine*>(pLineEnt->clone());

				//mirror the polyline across the symetry axis
				AcGeLine3d acGeLine3D(AcGePoint3d(sp.x, sp.y, 0), AcGePoint3d(ep.x, ep.y, 0));
				AcGeMatrix3d mir;
				mir.setToMirroring(acGeLine3D);
				pPolyEntMir->transformBy(mir);
				pLineEntMir->transformBy(mir);

				//// scale the pEntmir
				//AcGeMatrix3d matScale = AcGeMatrix3d::scaling(scale, AcGePoint3d(pkPt.x, pkPt.y, 0));
				//pPolyEntMir->transformBy(matScale);

				AcDbObjectId polyMirId;
				pBlkTableRecord->appendAcDbEntity(polyMirId, pPolyEntMir);
				pPolyEntMir->close();

				AcDbObjectId lineMirId;
				pBlkTableRecord->appendAcDbEntity(lineMirId, pLineEntMir);
				pLineEntMir->close();
			}

			// Add the AcDbLine entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(lineId, pLineEnt);

			// Add the AcDbPolyline entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(polyId, pPolyEnt);

			pBlkTableRecord->close();
			pLineEnt->close();
			pPolyEnt->close();
		}
	}

	static void drawDAngle(const TCHAR* section, const TCHAR* view, const double& scale)
	{
		int index = 0;

		for (int i = 0; i < 8; ++i)
		{
			std::string str = pro[i].section;
			std::wstring proName(str.length(), L' '); // Make room for characters
			// Copy string to wstring.
			std::copy(str.begin(), str.end(), proName.begin());
			if (_tcscmp(proName.c_str(), section) == 0)
			{
				index = i;
				break;
			}
		}

		auto profil = pro[index];
		if (_tcscmp(view, ACRX_T("Plan")) == 0)
		{
			DrawAnglePlanView(profil, scale);
		}
		else if (_tcscmp(view, ACRX_T("Section")) == 0)
		{
			DrawAngleSectionView(profil, scale);
		}
		else if (_tcscmp(view, ACRX_T("Top")) == 0)
		{
			DrawAngleTopView(profil, scale);
		}
	}

	static void DrawNPUSectionView(const NProfil& profil, const double& scale)
	{
		AcDbDatabase *pCurDb;
		AcDbBlockTable *pBlkTable;
		AcDbBlockTableRecord *pBlkTableRecord;

		//Adesk::Boolean firstPick = Adesk::kTrue;

		// Polylines are created in terms of the
		// Entity Coordinate System as opposed to
		// the World Coordinate System. If we are
		// using a UCS other than WCS we need to
		// translate back to the ECS.

		AcGeMatrix3d ucsMat;
		AcGeMatrix2d ucsMat2d;

		acdbUcsMatrix(ucsMat);
		ucsMat2d(0, 0) = ucsMat(0, 0);
		ucsMat2d(0, 1) = ucsMat(0, 1);
		ucsMat2d(0, 2) = ucsMat(0, 3);
		ucsMat2d(1, 0) = ucsMat(1, 0);
		ucsMat2d(1, 1) = ucsMat(1, 1);
		ucsMat2d(1, 2) = ucsMat(1, 3);

		Adesk::Boolean keepPicking = Adesk::kTrue;
		const double pi = std::acos(-1);

		while (keepPicking)
		{
			AcDbPolyline *pPolyEnt;
			AcDbObjectId polyId;

			AcDbLine *pLineEnt;
			AcDbObjectId lineId;

			AcGePoint2d sp, ep, pkPt;
			AcGePoint3d spL, epL;
			AcGePoint2dArray arPts;
			ads_point pick, secondPick;

			int retCode;
			int numPts;

			retCode = acedGetPoint(NULL, L"\nPick DNPU start point: ", pick);
			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}
			retCode = acedGetPoint(pick, L"\nPick DNPU end point: ", secondPick);
			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}

			sp.x = pick[X];
			sp.y = pick[Y];

			ep.x = secondPick[X];
			ep.y = secondPick[Y];

			double dblAngle = acutAngle(reinterpret_cast<double*>((ads_point*)(&sp)),
				reinterpret_cast<double*>((ads_point*)(&ep)));
			double dbl90Deg = 90 * pi / 180;

			double h, tf;
			h = scale * profil.h;
			tf = scale * profil.tf;

			spL.x = sp.x + (h / 2 - tf) * sin(dblAngle);
			spL.y = sp.y - (h / 2 - tf) * sin(dbl90Deg - dblAngle);
			spL.z = 0;
			epL.x = ep.x + (h / 2 - tf) * sin(dblAngle);
			epL.y = ep.y - (h / 2 - tf) * sin(dbl90Deg - dblAngle);
			epL.z = 0;

			// Create the line entity
			pLineEnt = new AcDbLine(spL, epL);

			arPts.removeAll();

			// Append the sideview rectangle corner points to the AcGePoint2dArray
			arPts.append(AcGePoint2d(sp.x - (h / 2)*sin(dblAngle), sp.y + (h / 2)*sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(ep.x - (h / 2)*sin(dblAngle), ep.y + (h / 2)*sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(ep.x + (h / 2)*sin(dblAngle), ep.y - (h / 2)*sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(sp.x + (h / 2)*sin(dblAngle), sp.y - (h / 2)*sin(dbl90Deg - dblAngle)));

			numPts = arPts.length();

			pCurDb = acdbHostApplicationServices()->workingDatabase();
			// Get the model space Block Table Record
			pCurDb->getBlockTable(pBlkTable, AcDb::kForRead);
			pBlkTable->getAt(ACDB_MODEL_SPACE, pBlkTableRecord, AcDb::kForWrite);
			pBlkTable->close();

			pPolyEnt = new AcDbPolyline(numPts);

			// Process the AcGePoint2dArray and add verticies to
			// our polyline.
			for (int idx = 0; idx < numPts; idx++)
			{
				pkPt = arPts.at(idx);
				pkPt.transformBy(ucsMat2d);
				pPolyEnt->addVertexAt(idx, pkPt);
			}

			pPolyEnt->setClosed(Adesk::kTrue);

			// Create a copy of the original line
			AcDbLine *pLineEntMir = static_cast<AcDbLine*>(pLineEnt->clone());

			//mirror the polyline across the symetry axis
			AcGeLine3d acGeLine3D(AcGePoint3d(sp.x, sp.y, 0), AcGePoint3d(ep.x, ep.y, 0));
			AcGeMatrix3d mir;
			mir.setToMirroring(acGeLine3D);
			pLineEntMir->transformBy(mir);

			AcDbObjectId lineMirId;
			pBlkTableRecord->appendAcDbEntity(lineMirId, pLineEntMir);
			pLineEntMir->close();

			// Add the AcDbLine entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(lineId, pLineEnt);

			// Add the AcDbPolyline entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(polyId, pPolyEnt);

			pBlkTableRecord->close();
			pLineEnt->close();
			pPolyEnt->close();
		}
	}

	static void DrawNPUTopView(const NProfil& profil, const double& scale)
	{
		AcDbDatabase *pCurDb;
		AcDbBlockTable *pBlkTable;
		AcDbBlockTableRecord *pBlkTableRecord;

		//Adesk::Boolean firstPick = Adesk::kTrue;

		// Polylines are created in terms of the
		// Entity Coordinate System as opposed to
		// the World Coordinate System. If we are
		// using a UCS other than WCS we need to
		// translate back to the ECS.

		AcGeMatrix3d ucsMat;
		AcGeMatrix2d ucsMat2d;

		acdbUcsMatrix(ucsMat);
		ucsMat2d(0, 0) = ucsMat(0, 0);
		ucsMat2d(0, 1) = ucsMat(0, 1);
		ucsMat2d(0, 2) = ucsMat(0, 3);
		ucsMat2d(1, 0) = ucsMat(1, 0);
		ucsMat2d(1, 1) = ucsMat(1, 1);
		ucsMat2d(1, 2) = ucsMat(1, 3);

		Adesk::Boolean keepPicking = Adesk::kTrue;
		Adesk::Boolean hasSymmetry = Adesk::kTrue;
		const double pi = std::acos(-1);

		while (keepPicking)
		{
			AcDbPolyline *pPolyEnt;
			AcDbObjectId polyId;

			AcDbLine *pLineEnt;
			AcDbObjectId lineId;

			AcGePoint2d sp, ep, pkPt;
			AcGePoint3d spL, epL;
			AcGePoint2dArray arPts;
			ads_point pick, secondPick;

			int retCode;
			int numPts;

			retCode = acedGetPoint(NULL, L"\nPick DNPU start point: ", pick);
			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}
			retCode = acedGetPoint(pick, L"\nPick DNPU end point: ", secondPick);
			if (retCode != RTNORM)
			{
				keepPicking = Adesk::kFalse;
				break;
			}

			sp.x = pick[X];
			sp.y = pick[Y];

			ep.x = secondPick[X];
			ep.y = secondPick[Y];

			double dblAngle = acutAngle(reinterpret_cast<double*>((ads_point*)(&sp)),
				reinterpret_cast<double*>((ads_point*)(&ep)));
			double dbl90Deg = 90 * pi / 180;

			double b, tw, dis;
			b = scale * profil.b;
			tw = scale * profil.tw;
			dis = scale * 5;

			spL.x = sp.x + (dis + tw) * sin(dblAngle);
			spL.y = sp.y - (dis + tw) * sin(dbl90Deg - dblAngle);
			spL.z = 0;
			epL.x = ep.x + (dis + tw) * sin(dblAngle);
			epL.y = ep.y - (dis + tw) * sin(dbl90Deg - dblAngle);
			epL.z = 0;

			// Create the line entity
			pLineEnt = new AcDbLine(spL, epL);
			createLinetype();
			pLineEnt->setLinetype(L"T_E_S_T");

			arPts.removeAll();

			// Append the sideview rectangle corner points to the AcGePoint2dArray
			arPts.append(AcGePoint2d(sp.x + dis * sin(dblAngle), sp.y - dis * sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(ep.x + dis * sin(dblAngle), ep.y - dis * sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(ep.x + (dis + b)*sin(dblAngle), ep.y - (dis + b)*sin(dbl90Deg - dblAngle)));
			arPts.append(AcGePoint2d(sp.x + (dis + b)*sin(dblAngle), sp.y - (dis + b)*sin(dbl90Deg - dblAngle)));

			numPts = arPts.length();

			pCurDb = acdbHostApplicationServices()->workingDatabase();
			// Get the model space Block Table Record
			pCurDb->getBlockTable(pBlkTable, AcDb::kForRead);
			pBlkTable->getAt(ACDB_MODEL_SPACE, pBlkTableRecord, AcDb::kForWrite);
			pBlkTable->close();

			pPolyEnt = new AcDbPolyline(numPts);

			// Process the AcGePoint2dArray and add verticies to
			// our polyline.
			for (int idx = 0; idx < numPts; idx++)
			{
				pkPt = arPts.at(idx);
				pkPt.transformBy(ucsMat2d);
				pPolyEnt->addVertexAt(idx, pkPt);
			}

			pPolyEnt->setClosed(Adesk::kTrue);

			if (hasSymmetry)
			{
				// Create a copy of the original polyline
				AcDbPolyline *pPolyEntMir = static_cast<AcDbPolyline*>(pPolyEnt->clone());
				// Create a copy of the original line
				AcDbLine *pLineEntMir = static_cast<AcDbLine*>(pLineEnt->clone());

				//mirror the polyline across the symetry axis
				AcGeLine3d acGeLine3D(AcGePoint3d(sp.x, sp.y, 0), AcGePoint3d(ep.x, ep.y, 0));
				AcGeMatrix3d mir;
				mir.setToMirroring(acGeLine3D);
				pPolyEntMir->transformBy(mir);
				pLineEntMir->transformBy(mir);

				//// scale the pEntmir
				//AcGeMatrix3d matScale = AcGeMatrix3d::scaling(scale, AcGePoint3d(pkPt.x, pkPt.y, 0));
				//pPolyEntMir->transformBy(matScale);

				AcDbObjectId polyMirId;
				pBlkTableRecord->appendAcDbEntity(polyMirId, pPolyEntMir);
				pPolyEntMir->close();

				AcDbObjectId lineMirId;
				pBlkTableRecord->appendAcDbEntity(lineMirId, pLineEntMir);
				pLineEntMir->close();
			}

			// Add the AcDbLine entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(lineId, pLineEnt);

			// Add the AcDbPolyline entity to the Block
			// Table Record
			pBlkTableRecord->appendAcDbEntity(polyId, pPolyEnt);

			pBlkTableRecord->close();
			pLineEnt->close();
			pPolyEnt->close();
		}
	}

	static void DrawNPUPlanView(const NProfil& profil, const double& scale)
	{

	}

	static void drawDNPU(const TCHAR* section, const TCHAR* view, const double& scale)
	{
		int index = 0;

		for (int i = 0; i < 16; ++i)
		{
			std::string str = npro[i].section;
			std::wstring proName(str.length(), L' '); // Make room for characters
			// Copy string to wstring.
			std::copy(str.begin(), str.end(), proName.begin());
			if (_tcscmp(proName.c_str(), section) == 0)
			{
				index = i;
				break;
			}
		}

		auto profil = npro[index];
		if (_tcscmp(view, ACRX_T("Plan")) == 0)
		{
			DrawNPUPlanView(profil, scale);
		}
		else if (_tcscmp(view, ACRX_T("Section")) == 0)
		{
			DrawNPUSectionView(profil, scale);
		}
		else if (_tcscmp(view, ACRX_T("Top")) == 0)
		{
			DrawNPUTopView(profil, scale);
		}
	}

	static void getScale(const TCHAR* section, const TCHAR* type, const TCHAR* view)
	{
		//TCHAR kw[64];

		int rc; // return code

		double scale = 0;

		acedInitGet(RSG_NOZERO, ACRX_T("1 2 5 10 20 25 50 100"));
		rc = acedGetReal(ACRX_T("\nEnter Scale : [1/0.5/0.2/0.1/0.05/0.04/0.02/0.01] <1>: "), &scale);

		switch (rc)
		{
		case RTCAN:
			acutPrintf(L"\nUser canceled");
			break;
		case RTERROR:
			acutPrintf(L"\nError in acedGetKword function");
			break;
		case RTNONE:
			// If the user presses the [ENTER] key
			// we take this as a "Yes"			
			break;
		case RTNORM:
			//acutPrintf(L"\nUser entered scale %lf", scale);
			if (_tcscmp(type, ACRX_T("ANGLE")) == 0)
			{
				drawDAngle(section, view, scale);
			}
			else if (_tcscmp(type, ACRX_T("NPU")) == 0)
			{
				drawDNPU(section, view, scale);
			}

			break;
		}
	}

	static void selectMode(const TCHAR* section, const TCHAR* type)
	{
		TCHAR kw[64];

		int rc; // return code

		acedInitGet(NULL, L"Plan Section Top");
		rc = acedGetKword(L"\nSelect View - [Plan/Section/Top]<Plan>: ", kw);

		switch (rc)
		{
		case RTCAN:
			acutPrintf(L"\nUser canceled");
			break;
		case RTERROR:
			acutPrintf(L"\nError in acedGetKword function");
			break;
		case RTNONE:
			// If the user presses the [ENTER] key
			// we take this as a "Yes"			
			break;
		case RTNORM:
			getScale(section, type, kw);
			break;
		}
	}

	static void DYNAMyGroupDrawDAngle()
	{
		TCHAR kw[64];
		TCHAR type[64];
		int rc; // return code

		acedInitGet(NULL, L"2L50 2L60 2L70 2L80 2L90 2L100 2L110 2L120");
		rc = acedGetKword(L"\nSelect DAngle - [2L50/2L60/2L70/2L80/2L90/2L100/2L110/2L120]<2L50>: ", kw);

		switch (rc)
		{
		case RTCAN:
			acutPrintf(L"\nUser canceled");
			break;
		case RTERROR:
			acutPrintf(L"\nError in acedGetKword function");
			break;
		case RTNONE:
			// If the user presses the [ENTER] key
			// we take this as a "Yes"			
			break;
		case RTNORM:
			_tcscpy(type, L"ANGLE");
			selectMode(kw, type);
			break;
		}
	}

	static void DYNAMyGroupDrawDNPU()
	{
		TCHAR kw[64];
		TCHAR type[64];
		int rc; // return code

		acedInitGet(NULL, L"2NPU80 2NPU100 2NPU120 2NPU140 2NPU160 2NPU180 2NPU200 2NPU220 2NPU240 2NPU260 2NPU280 2NPU300 2NPU320 2NPU350 2NPU380 2NPU400");
		rc = acedGetKword(L"\nSelect DNPU - [2NPU80/2NPU100/2NPU120/2NPU140/2NPU160/2NPU180/2NPU200/2NPU220/2NPU240/2NPU260/2NPU280/2NPU300/2NPU320/2NPU350/2NPU380/2NPU400]<2NPU80>: ", kw);

		switch (rc)
		{
		case RTCAN:
			acutPrintf(L"\nUser canceled");
			break;
		case RTERROR:
			acutPrintf(L"\nError in acedGetKword function");
			break;
		case RTNONE:
			// If the user presses the [ENTER] key
			// we take this as a "Yes"			
			break;
		case RTNORM:
			_tcscpy(type, L"NPU");
			selectMode(kw, type);
			break;
		}
	}


	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CDoubleAngle2020App, DYNAMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void DYNAMyGroupMyCommand () {
		// Put your command code here

	}

	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CDoubleAngle2020App, DYNAMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void DYNAMyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CDoubleAngle2020App, DYNAMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void DYNAMyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CDoubleAngle2020App class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CDoubleAngle2020App, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}
	
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CDoubleAngle2020App)

ACED_ARXCOMMAND_ENTRY_AUTO(CDoubleAngle2020App, DYNAMyGroup, DrawDAngle, DrawDAngleLocal, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDoubleAngle2020App, DYNAMyGroup, DrawDNPU, DrawDNPULocal, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDoubleAngle2020App, DYNAMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDoubleAngle2020App, DYNAMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CDoubleAngle2020App, DYNAMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
ACED_ADSSYMBOL_ENTRY_AUTO(CDoubleAngle2020App, MyLispFunction, false)

