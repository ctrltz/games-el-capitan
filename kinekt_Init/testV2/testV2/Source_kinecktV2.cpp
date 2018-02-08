#include <windows.h>
#include <Shlobj.h>
#include <d2d1.h>
#include <Kinect.h>
#include <iostream>

using namespace std;

IBodyFrameReader*       m_pBodyFrameReader;
IKinectSensor*          m_pKinectSensor;
ICoordinateMapper*      m_pCoordinateMapper;
HWND                    m_hWnd;
ID2D1HwndRenderTarget*  m_pRenderTarget;

static const int        cDepthWidth = 512;
static const int        cDepthHeight = 424;

void                    Update();

HRESULT                 InitializeDefaultSensor();
void                    ProcessBody(INT64 nTime, int nBodyCount, IBody** ppBodies);
D2D1_POINT_2F           BodyToScreen(const CameraSpacePoint& bodyPoint, int width, int height);


template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}



void Update()
{
	if (!m_pBodyFrameReader)
	{
		return;
	}

	IBodyFrame* pBodyFrame = NULL;

	HRESULT hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);
	cout << SUCCEEDED(hr);

	if (SUCCEEDED(hr))
	{
		cout << "a";
		INT64 nTime = 0;

		hr = pBodyFrame->get_RelativeTime(&nTime);

		IBody* ppBodies[BODY_COUNT] = { 0 };

		if (SUCCEEDED(hr))
		{
			hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
		}

		if (SUCCEEDED(hr))
		{
			ProcessBody(nTime, BODY_COUNT, ppBodies);
		}

		for (int i = 0; i < _countof(ppBodies); ++i)
		{
			SafeRelease(ppBodies[i]);
		}

	SafeRelease(pBodyFrame);

	}
}

HRESULT InitializeDefaultSensor()
{
	HRESULT hr;

	hr = GetDefaultKinectSensor(&m_pKinectSensor);
	if (FAILED(hr))
	{
		return hr;
	}

	if (m_pKinectSensor)
	{
		// Initialize the Kinect and get coordinate mapper and the body reader
		IBodyFrameSource* pBodyFrameSource = NULL;

		hr = m_pKinectSensor->Open();

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
		}
		
		if (SUCCEEDED(hr))
		{
			hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
		}
		
		SafeRelease(pBodyFrameSource);

		if (!m_pKinectSensor || FAILED(hr))
		{
			int a;
			cout << "No ready Kinect found!";
			cin >> a;
			return E_FAIL;
		}
		
	}
	return hr;
}

void ProcessBody(INT64 nTime, int nBodyCount, IBody** ppBodies)
{
	if (m_hWnd)
	{
		HRESULT hr = S_OK;
		if (SUCCEEDED(hr) && m_pRenderTarget && m_pCoordinateMapper)
		{
			m_pRenderTarget->BeginDraw();
			m_pRenderTarget->Clear();
			/*
			RECT rct;
			GetClientRect(GetDlgItem(m_hWnd, IDC_VIDEOVIEW), &rct);
			int width = rct.right;
			int height = rct.bottom;
			*/
			int width = 640;
			int height = 480;


			for (int i = 0; i < nBodyCount; ++i)
			{
				IBody* pBody = ppBodies[i];
				if (pBody)
				{
					BOOLEAN bTracked = false;
					hr = pBody->get_IsTracked(&bTracked);

					if (SUCCEEDED(hr) && bTracked)
					{
						Joint joints[JointType_Count];
						D2D1_POINT_2F jointPoints[JointType_Count];
						HandState leftHandState = HandState_Unknown;
						HandState rightHandState = HandState_Unknown;

						pBody->get_HandLeftState(&leftHandState);
						pBody->get_HandRightState(&rightHandState);

						hr = pBody->GetJoints(_countof(joints), joints);
						if (SUCCEEDED(hr))
						{
							for (int j = 0; j < _countof(joints); ++j)
							{
								jointPoints[j] = BodyToScreen(joints[j].Position, width, height);
							}
							/*
							DrawBody(joints, jointPoints);

							DrawHand(leftHandState, jointPoints[JointType_HandLeft]);
							DrawHand(rightHandState, jointPoints[JointType_HandRight]);
							*/
							cout << jointPoints[JointType_HandLeft].x;
						}
					}
				}
			}

			hr = m_pRenderTarget->EndDraw();		
		}
	}
}

D2D1_POINT_2F BodyToScreen(const CameraSpacePoint& bodyPoint, int width, int height)
{
	// Calculate the body's position on the screen
	DepthSpacePoint depthPoint = { 0 };
	m_pCoordinateMapper->MapCameraPointToDepthSpace(bodyPoint, &depthPoint);

	float screenPointX = static_cast<float>(depthPoint.X * width) / cDepthWidth;
	float screenPointY = static_cast<float>(depthPoint.Y * height) / cDepthHeight;

	return D2D1::Point2F(screenPointX, screenPointY);
}

int main() {
	
	while (true) {
		InitializeDefaultSensor();
		Update();
		SafeRelease(m_pBodyFrameReader);

		// done with coordinate mapper
		SafeRelease(m_pCoordinateMapper);

		// close the Kinect Sensor
		if (m_pKinectSensor)
		{
			m_pKinectSensor->Close();
		}

		SafeRelease(m_pKinectSensor);
	}
}

