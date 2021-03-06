///////////////////////////////////////////////////////
// Beehive: A complete SEGA Mega Drive content tool
//
// (c) 2016 Matt Phillips, Big Evil Corporation
// http://www.bigevilcorporation.co.uk
// mattphillips@mail.com
// @big_evil_corp
//
// Licensed under GPLv3, see http://www.gnu.org/licenses/gpl-3.0.html
///////////////////////////////////////////////////////

#pragma once

#include <ion/beehive/Animation.h>

#include "UIBase.h"
#include "ViewPanel.h"
#include "KeyframePanel.h"

#include <wx/timer.h>

class TimelinePanel : public TimelinePanelBase
{
public:
	TimelinePanel(MainWindow& mainWindow, Project& project, ion::render::Renderer& renderer, wxGLContext& glContext, RenderResources& renderResources, wxWindow *parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER, const wxString& name = wxPanelNameStr);
	virtual ~TimelinePanel();

	void PopulateActors();

	void SetCurrentActor(GameObjectId actorId);
	AnimationId GetCurrentAnimation() const;

	virtual void Refresh(bool eraseBackground = true, const wxRect *rect = NULL);

	void EventHandlerTimer(wxTimerEvent& event);
	void EventHandlerTimeline(TimeEvent& event);
	void EventHandlerTrack(TrackEvent& event);
	void EventHandlerSection(SectionEvent& event);
	void EventHandlerKeyframe(KeyframeEvent& event);

protected:

	virtual void OnSpinSpeed(wxSpinEvent& event);
	virtual void OnSelectAnimation(wxCommandEvent& event);
	virtual void OnSelectActor(wxCommandEvent& event);
	virtual void OnSelectSpriteAnim(wxCommandEvent& event);
	virtual void OnToolAddAnim(wxCommandEvent& event);
	virtual void OnToolDeleteAnim(wxCommandEvent& event);
	virtual void OnToolLoopToggle(wxCommandEvent& event);
	virtual void OnToolKeyframeReplace(wxCommandEvent& event);
	virtual void OnToolKeyframeInsert(wxCommandEvent& event);
	virtual void OnToolKeyframeEnd(wxCommandEvent& event);
	virtual void OnToolKeyframeDelete(wxCommandEvent& event);
	virtual void OnToolPlay(wxCommandEvent& event);
	virtual void OnToolStop(wxCommandEvent& event);
	virtual void OnToolStepLeft(wxCommandEvent& event);
	virtual void OnToolStepRight(wxCommandEvent& event);
	virtual void OnToolRewind(wxCommandEvent& event);
	virtual void OnToolFastForward(wxCommandEvent& event);
	virtual void OnToolIsolateObject(wxCommandEvent& event);
	virtual void OnChkExportLocalSpace(wxCommandEvent& event);
	virtual void OnResize(wxSizeEvent& event);

	//Right-click menu callback
	void OnContextMenuClick(wxCommandEvent& event);

private:
	enum MenuItems
	{
		eMenuInsertKeyframeLeft,
		eMenuInsertKeyframeRight,
		eMenuDeleteKeyframe,
		eMenuSetSpriteAnimLength
	};

	void PopulateAnimations();
	void PopulateTimeline(Animation& animation);

	void SyncActor(AnimationActor& actor);
	void SyncAllActors();

	void RecalculateLenth(Animation& animation);

	void SetSliderFrame(float frame);
	void Keyframe(AnimationActor* actor, float frame, int trackMask = ((1 << eTrackCount)-1));
	void SetAnimLength(Animation& animation, const AnimationActor& actor);
	void ShuffleKeyframesRight(AnimationActor& actor, float time);
	void RecalcKeyframeTimes(AnimationActor& actor);

	void KeyframeModified(KeyframePanel::KeyframeId keyframeId, float time, float length);
	void KeyframeDeleted(KeyframePanel::KeyframeId keyframeId);

	static const char* s_trackNames[eTrackCount];

	MainWindow& m_mainWindow;
	Project& m_project;

	std::vector<AnimationId> m_animCache;
	std::vector<AnimationActor*> m_actorCache;
	std::vector<std::pair<SpriteSheetId, SpriteAnimId>> m_spriteSheetCache;

	//Track cache, for matching KeyframePanel callbacks to tracks
	struct TrackCache
	{
		AnimationActor* actor;
		GameObject* gameObject;
		AnimationTracks trackType;
	};

	std::map<KeyframePanel::SectionId, AnimationActor*> m_sectionCache;
	std::map<KeyframePanel::TrackId, TrackCache> m_trackCache;

	//Keyframe cache, for matching KeyframePanel callbacks to keyframes
	template <typename T> struct KeyframeCache
	{
		AnimationActor* actor;
		GameObject* gameObject;
		ion::render::AnimationTrack<T>* track;
		int keyframeIdx;
	};

	std::map<KeyframePanel::KeyframeId, KeyframeCache<ion::Vector2i>> m_keyframeCachePosition;
	std::map<KeyframePanel::KeyframeId, KeyframeCache<std::pair<SpriteSheetId, SpriteAnimId>>> m_keyframeCacheSpriteAnim;

	AnimationId m_animationId;
	Animation* m_animation;

	AnimationTracks m_selectedTrackId;
	GameObjectId m_selectedActorId;
	AnimationActor* m_selectedActor;

	//Timer
	u64 m_prevClock;
	wxTimer m_timer;

	int m_contextMenuColIdx;
};