#pragma once
#include<memory>
#include<vector>

namespace GPS
{
	class SateliteInfo;
	typedef std::shared_ptr<SateliteInfo> Ptr_SatInfo;
	typedef std::vector<SateliteInfo> SatInfoVec;

	class Satellite
	{
	public:
		Satellite();
		~Satellite();

		void setSatinfo(SatInfoVec satinfoVec);
		SatInfoVec getSatInfo();
		void setSateInView(int satInView);
		int getSatInView();
		

	private:
		SatInfoVec _satInfo;
		int _sateInView;

	protected:

	};
}
