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
	// 1. FocusedUI Ȯ��(ã��)
	UI* focusingUI = FindFocusingUI();

	// ��Ŀ�̵� UI�� ���ٸ� �ٷ� Update����
	if (focusingUI == nullptr) return;
	SetFocusingUI(focusingUI);
	
	// 2. outer UI ����, �ڽ� UI���� ���� Ÿ���� UI�����´�.
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

			// hover�� ���¿��� ui�� �������� �ְ� ������ �ֱ� ������
			if (targetUI->GetLBTNDownOnThisUI())
			{
				targetUI->EVENT_MOUSE_LBTN_CLICK_UI();
			}

			// ���� ��ư ����, ������ üũ�� �ٽ� �����Ѵ�.
			targetUI->SetLBTNDownOnThisUI(false);
		}
	}
}

void UIManager::SetForceFocusingUI(UI* outerUI)
{
	// �̹� ��Ŀ�� ���� ����̰ų� nullptr������ ���(��Ŀ���� �� ���� �ش޶�� �ϴ°��
	if (GetFocusingUI() == outerUI || nullptr == outerUI)
	{
		SetFocusingUI(outerUI);
		return;
	}

	SetFocusingUI(outerUI);
	
	Scene* curScene = SCENE->GetCurrentScene();
	vector<Object*>& vecUI = curScene->GetUIObjects();

	// ���� ��ư ������ ��Ȳ �߻��ߴ�.
	vector<Object*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		bool hoverOn = static_cast<UI*>(*iter)->GetMouseHoverOnThisUI();

		if (GetFocusingUI() == static_cast<UI*>(*iter))
		{
			break;
		}
	}

	// ���� �ڷ� ������ ������ ������ ���� ���ʿ� ��ġ�ϵ��� �������ش�.
	vecUI.erase(iter);
	vecUI.push_back(GetFocusingUI());
}

UI* UIManager::GetTargetUI(UI* outerUI)
{
	// 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
	// 
	// 2. Ÿ�� UI ���� �� �켱������ ���� ������ �� ���� ������ �ڽ� UI�̴�.	
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

		// TODO : �˻�
		// ������ �´ٸ� targetUI ����
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

	// ���ʹ�ư ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
	if (releaseLBTN)
	{
		for (UI* ui : vecNoneTargetUI)
		{
			NULL_PTR_CHECK(ui);
			ui->SetLBTNDownOnThisUI(false);
		}
	}

	// nullptr ��ȯ �����ϴ�. (�ƹ��� Ÿ���� ���� ���)
	return targetUI;
}

UI* UIManager::FindFocusingUI()
{
	bool pressedLBTN = KEY_PRESSED(KEYES::LBTN);
	Scene* curScene = SCENE->GetCurrentScene();
	vector<Object*>& vecUI = curScene->GetUIObjects();

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	UI* focusedUI = GetFocusingUI();

	// �������� ���� == ��Ŀ�̵Ȱ� ���� return.
	if (!pressedLBTN)
	{
		return focusedUI;
	}

	// ���� ��ư ������ ��Ȳ �߻��ߴ�.
	vector<Object*>::iterator targetIter = vecUI.end();
	vector<Object*>::iterator iter = vecUI.begin();

	// CloseThisUI ȣ���� ��� RootUI���� ��� UI�� ���� Hover�� false�� �����ؾ��Ѵ�.
	// �׷��� ������ hoverOn�� true�� ����Ǿ� focusedUI �״�� ��ȯ�Ѵ�.
	for (; iter != vecUI.end(); ++iter)
	{
		bool hoverOn = static_cast<UI*>(*iter)->GetMouseHoverOnThisUI();

		if (pressedLBTN && hoverOn)
		{
			focusedUI = static_cast<UI*>(*iter);
			targetIter = iter;
		}
	}

	// Ÿ���� �� ã�� ���
	if (targetIter == vecUI.end())
	{
		return nullptr;
	}

	// ���� �ڷ� ������ ������ ������ ���� ���ʿ� ��ġ�ϵ��� �������ش�.
	// �ް����� �ȵǴ°� ������ ���Ҹ� iterator�� ����� �� ������ ���� �����͸� ����°� �ƴϴ�.
	// ���� ������ ���� �Ҹ��ڿ��� �����Ѵ�.
	focusedUI = static_cast<UI*>(*targetIter);
	vecUI.erase(targetIter);
	vecUI.push_back(focusedUI);
	return focusedUI;
}
