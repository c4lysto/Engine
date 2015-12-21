
#include "Application/AppEntryPoint.h"

int main(int argc, char** argv)
{
	int returnCode = -1;

	if(recon::AppEntryPoint::InitEntryPoint(argc, argv))
	{
		returnCode = recon::AppEntryPoint::ExecuteApp();

		recon::AppEntryPoint::ShutdownEntryPoint();
	}

	return returnCode;
}