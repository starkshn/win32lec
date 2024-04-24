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
	// 1. FocusedUI 확인(찾기)
	UI* focusingUI = FindFocusingUI();

	// 포커싱된 UI가 없다면 바로 Update종료
	if (focusingUI == nullptr) return;
	SetFocusingUI(focusingUI);
	
	// 2. outer UI 포함, 자식 UI들중 실제 타겟팅 UI가져온다.
	UI* targetUI = GetTargetUI(focusingUI);

	bool pressedLBTN = KEY_PRESSED(KEYES::LBTN);
	bool releaseLBTN = KEY_RELEASED(KEYES::LBTN);

	if (nullptr != targetUI)
	{
		targetUI->EVENT_MOUSE_HOVERON_UI();

		if (pressedLBTN)
		{
			targetUI->EVENT_MOUSE_LBTN_DOWN_UI();
			targetUI->SetLBTNDownOnThisUI(true);
		}
		else if (releaseLBTN)
		{
			targetUI->EVENT_MOUSE_LBTN_UP_UI();

			// hover된 상태에서 ui를 눌린적도 있고 땐적도 있기 때문에
			if (targetUI->GetLBTNDownOnThisUI())
			{
				targetUI->EVENT_MOUSE_LBTN_CLICK_UI();
			}

			// 왼쪽 버튼 때면, 눌렀던 체크를 다시 해제한다.
			targetUI->SetLBTNDownOnThisUI(false);
		}
	}
}

void UIManager::SetForceFocusingUI(UI* outerUI)
{
	// 이미 포커싱 중인 경우이거나 nullptr들어오는 경우(포커싱을 다 해제 해달라고 하는경우
	if (GetFocusingUI() == outerUI || nullptr == outerUI)
	{
		SetFocusingUI(outerUI);
		return;
	}

	SetFocusingUI(outerUI);
	
	Scene* curScene = SCENE->GetCurrentScene();
	vector<Object*>& vecUI = curScene->GetUIObjects();

	// 왼쪽 버튼 누르는 상황 발생했다.
	vector<Object*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		bool hoverOn = static_cast<UI*>(*iter)->GetMouseHoverOnThisUI();

		if (GetFocusingUI() == static_cast<UI*>(*iter))
		{
			break;
		}
	}

	// 가장 뒤로 보내서 렌더링 순서상 가장 앞쪽에 위치하도록 수정해준다.
	vecUI.erase(iter);
	vecUI.push_back(GetFocusingUI());
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

UI* UIManager::FindFocusingUI()
{
	bool pressedLBTN = KEY_PRESSED(KEYES::LBTN);
	Scene* curScene = SCENE->GetCurrentScene();
	vector<Object*>& vecUI = curScene->GetUIObjects();

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다.
	UI* focusedUI = GetFocusingUI();

	// 눌린적이 없다 == 포커싱된게 없다 return.
	if (!pressedLBTN)
	{
		return focusedUI;
	}

	// 왼쪽 버튼 누르는 상황 발생했다.
	vector<Object*>::iterator targetIter = vecUI.end();
	vector<Object*>::iterator iter = vecUI.begin();

	// CloseThisUI 호출한 경우 RootUI부터 모든 UI에 대한 Hover를 false로 변경해야한다.
	// 그렇지 않으면 hoverOn이 true로 변경되어 focusedUI 그대로 반환한다.
	for (; iter != vecUI.end(); ++iter)
	{
		bool hoverOn = static_cast<UI*>(*iter)->GetMouseHoverOnThisUI();

		if (pressedLBTN && hoverOn)
		{
			focusedUI = static_cast<UI*>(*iter);
			targetIter = iter;
		}
	}

	// 타겟을 못 찾은 경우
	if (targetIter == vecUI.end())
	{
		return nullptr;
	}

	// 가장 뒤로 보내서 렌더링 순서상 가장 앞쪽에 위치하도록 수정해준다.
	// 햇갈리면 안되는게 벡터의 원소를 iterator로 지우는 것 뿐이지 실제 포인터를 지우는게 아니다.
	// 실제 해제는 씬의 소멸자에서 진행한다.
	focusedUI = static_cast<UI*>(*targetIter);
	vecUI.erase(targetIter);
	vecUI.push_back(focusedUI);
	return focusedUI;
}
