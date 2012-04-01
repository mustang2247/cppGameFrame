/*
 * PetBaseMgr.cc
 *
 *  Created on: 2012-3-20
 *    
 */

#include <game/LoongBgSrv/base/PetBaseMgr.h>

PetBaseMgr::PetBaseMgr():
	curPetBaseNum_(0)
{
	init();
}

PetBaseMgr::~PetBaseMgr()
{
}

bool PetBaseMgr::init()
{
	petBaseList_[curPetBaseNum_].petId_ = 1;
	petBaseList_[curPetBaseNum_].petName_ = "傀儡巨人";
	petBaseList_[curPetBaseNum_].type_ = KONE_UNITTYPE;
	petBaseList_[curPetBaseNum_].speed_ = 0;
	petBaseList_[curPetBaseNum_].hp_ = 800;
	petBaseList_[curPetBaseNum_].skillNum_ = 2;
	petBaseList_[curPetBaseNum_].skillList_[0] = 1;
	petBaseList_[curPetBaseNum_].skillList_[1] = 2;
	curPetBaseNum_++;
	petBaseList_[curPetBaseNum_].petId_ = 2;
	petBaseList_[curPetBaseNum_].petName_ = "黑石大炮";
	petBaseList_[curPetBaseNum_].type_ = KSECOND_UNITTYPE;
	petBaseList_[curPetBaseNum_].speed_ = 0;
	petBaseList_[curPetBaseNum_].hp_ = 1000;
	petBaseList_[curPetBaseNum_].skillNum_ = 2;
	petBaseList_[curPetBaseNum_].skillList_[0] = 3;
	petBaseList_[curPetBaseNum_].skillList_[1] = 4;
	curPetBaseNum_++;
	petBaseList_[curPetBaseNum_].petId_ = 3;
	petBaseList_[curPetBaseNum_].petName_ = "地裂兽";
	petBaseList_[curPetBaseNum_].type_ = KTHREE_UNITTYPE;
	petBaseList_[curPetBaseNum_].speed_ = 0;
	petBaseList_[curPetBaseNum_].hp_ = 400;
	petBaseList_[curPetBaseNum_].skillNum_ = 2;
	petBaseList_[curPetBaseNum_].skillList_[0] = 5;
	petBaseList_[curPetBaseNum_].skillList_[1] = 6;

	return true;
}

void PetBaseMgr::shutdown()
{
}

const PetBase& PetBaseMgr::getPetBaseInfo(int16 petId) const
{
	static PetBase null;
	if (petId <= 0 || petId > sMaxPetId) return null;

	return petBaseList_[petId - 1];
}

bool PetBaseMgr::checkPetId(int16 petId)
{
	if (petId < 0 || petId > curPetBaseNum_) return false;
	return true;
}
