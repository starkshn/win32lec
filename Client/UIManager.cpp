#include "pch.h"
#include "UIManager.h"
#include "Scene.h"
#include "UI.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

void UIManager::Init()
{
	
}

void UIManager::Update()
{
	Scene* curScene = SCENE->GetCurrentScene();
	NULL_PTR_CHECK(curScene);

	const vector<Object*>& vecUIObjs = curScene->GetObjectsByType(OBJECT_TYPE::UI);
	
	bool pressedLBTN = KEY_PRESSED(KEYES::LBTN);
	bool releaseLBTN = KEY_RELEASED(KEYES::LBTN);
	
	for (uint32 i = 0; i < vecUIObjs.size(); ++i)
	{
		UI* ui = dynamic_cast<UI*>(vecUIObjs[i]);
		NULL_PTR_CHECK(ui);

		// outer UI 포함, 자식 UI들중 실제 타겟팅 UI가져온다.
		ui = GetTargetUI(ui);
		
		if (nullptr != ui)
		{
			ui->EVENT_MOUSE_HOVERON_UI();

			if (pressedLBTN)
			{
				ui->EVENT_MOUSE_LBTN_DOWN_UI();
				ui->SetLBTNDownOnThisUI(true);
			}
			else if (releaseLBTN)
			{
				ui->EVENT_MOUSE_LBTN_UP_UI();

				// hover된 상태에서 ui를 눌린적도 있고 땐적도 있기 때문에
				if (ui->GetLBTNDownOnThisUI())
				{
					ui->EVENT_MOUSE_LBTN_CLICK_UI();
				}

				// 왼쪽 버튼 때면, 눌렀던 체크를 다시 해제한다.
				ui->SetLBTNDownOnThisUI(false);
			}
		}
	}
}

UI* UIManager::GetTargetUI(UI* outerUI)
{
	// 1. 부모 UI 포함, 모든 자식들을 검사한다.
	// 
	// 2. 타겟 UI 둘중 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI이다.	
	bool releaseLBTN = KEY_RELEASED(KEYES::LBTN);

	UI* targetUI = nullptr;
	static deque<UI*> dq;
	static vector<UI*> vecNoneTargetUI;

	dq.clear();
	vecNoneTargetUI.clear();

	dq.push_back(outerUI);

	while (!dq.empty())
	{
		UI* curUI = dq.front();
		dq.pop_front();

		// TODO : 검사
		// 조건이 맞다면 targetUI 변경
		bool hoverOn = curUI->GetMouseHoverOnThisUI();

		if (hoverOn)
		{
			if (nullptr != targetUI)
			{
				vecNoneTargetUI.push_back(targetUI);
			}
			targetUI = curUI;
		}
		else
		{
			vecNoneTargetUI.push_back(curUI);
		}

		const vector<UI*>& vecInnerUI = curUI->GetInnerUI();
		for (UI* innerUI : vecInnerUI)
		{
			NULL_PTR_CHECK(innerUI);
			dq.push_back(innerUI);
		}
	}

	// 왼쪽버튼 때면, 눌렸던 체크를 다시 해제한다.
	if (releaseLBTN)
	{
		for (UI* ui : vecNoneTargetUI)
		{
			NULL_PTR_CHECK(ui);
			ui->SetLBTNDownOnThisUI(false);
		}
	}

	// nullptr 반환 가능하다. (아무런 타겟이 없는 경우)
	return targetUI;
}
