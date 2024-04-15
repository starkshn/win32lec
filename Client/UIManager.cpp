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

		// outer UI ����, �ڽ� UI���� ���� Ÿ���� UI�����´�.
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

				// hover�� ���¿��� ui�� �������� �ְ� ������ �ֱ� ������
				if (ui->GetLBTNDownOnThisUI())
				{
					ui->EVENT_MOUSE_LBTN_CLICK_UI();
				}

				// ���� ��ư ����, ������ üũ�� �ٽ� �����Ѵ�.
				ui->SetLBTNDownOnThisUI(false);
			}
		}
	}
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
