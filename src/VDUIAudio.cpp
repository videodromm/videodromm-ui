#include "VDUIAudio.h"

using namespace videodromm;

VDUIAudio::VDUIAudio(VDSettingsRef aVDSettings, VDSessionRef aVDSession) {
	mVDSettings = aVDSettings;
	mVDSession = aVDSession;
}
VDUIAudio::~VDUIAudio() {

}

void VDUIAudio::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mVDSettings->uiLargeW, mVDSettings->uiLargeH * 1.3), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mVDSettings->uiMargin, mVDSettings->uiYPosRow1), ImGuiSetCond_Once);
	sprintf(buf, "%s##inpt", mVDSession->getInputTextureName(0).c_str());
	ImGui::Begin(buf);
	{
		if (ImGui::CollapsingHeader("Audio", NULL, true, true))
		{
		ImGui::PushItemWidth(mVDSettings->mPreviewFboWidth*2);
		ImGui::Text("Position %d", mVDSession->getPosition(0));

		static int iFreq0 = mVDSession->getFreqIndex(0);
		sprintf(buf, "f0 %4.2f##f0", mVDSession->getFreq(0));
		if (ImGui::SliderInt(buf, &iFreq0, 0, mVDSession->getWindowSize()))
		{
			mVDSession->setFreqIndex(0, iFreq0);
		}
		static int iFreq1 = mVDSession->getFreqIndex(1);
		sprintf(buf, "f1 %4.2f##f1", mVDSession->getFreq(1));
		if (ImGui::SliderInt(buf, &iFreq1, 0, mVDSession->getWindowSize()))
		{
			mVDSession->setFreqIndex(1, iFreq1);
		} 

		static int iFreq2 = mVDSession->getFreqIndex(2);
		sprintf(buf, "f2 %4.2f##f2", mVDSession->getFreq(2));
		if (ImGui::SliderInt(buf, &iFreq2, 0, mVDSession->getWindowSize()))
		{
			mVDSession->setFreqIndex(2, iFreq2);
		}

		static int iFreq3 = mVDSession->getFreqIndex(3);
		sprintf(buf, "f3 %4.2f##f3", mVDSession->getFreq(3));
		if (ImGui::SliderInt(buf, &iFreq3, 0, mVDSession->getWindowSize()))
		{
			mVDSession->setFreqIndex(3, iFreq3);
		}

		(mVDSession->getFreqWSSend()) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4.0f, 0.8f, 0.8f));
		if (ImGui::Button("Send WS Freqs")) {
			mVDSession->toggleFreqWSSend();
		}
		ImGui::PopStyleColor(3);
		
		ImGui::PopItemWidth();
		}
		if (ImGui::CollapsingHeader("Tempo", NULL, true, true))
		{

			ImGui::PushItemWidth(mVDSettings->mPreviewFboWidth);
			if (ImGui::Button("x##spdx")) { mVDSettings->iSpeedMultiplier = 1.0; }
			ImGui::SameLine();
			ImGui::SliderFloat("speed x", &mVDSettings->iSpeedMultiplier, 0.01f, 5.0f, "%.1f");
			/* TODO
			ImGui::Text("Beat %d ", mVDSettings->iBeat);
			ImGui::SameLine();
			ImGui::Text("Beat Idx %d ", mVDAnimation->iBeatIndex);
			//ImGui::SameLine();
			//ImGui::Text("Bar %d ", mVDAnimation->iBar);
			if (ImGui::Button("x##bpbx")) { mVDSession->setControlValue("iBeat", 1); }
			ImGui::SameLine();
	 */
			ImGui::Text("beat %d ", mVDSession->getIntUniformValueByName("iBeat"));
			ImGui::SameLine();
			ImGui::Text("beats/bar %d ", mVDSession->getIntUniformValueByName("iBeatsPerBar"));

			ImGui::Text("Time %.2f", mVDSession->getFloatUniformValueByName("iTime"));
			ImGui::SameLine();
			ImGui::Text("Tempo Time %.2f", mVDSession->getFloatUniformValueByName("iTempoTime"));

			ImGui::Text("Trk %s %.2f", mVDSettings->mTrackName.c_str(), mVDSettings->liveMeter);
			ImGui::SameLine();
			//			ImGui::Checkbox("Playing", &mVDSettings->mIsPlaying);
			ImGui::Text("Tempo %.2f ", mVDSession->getBpm());

			if (ImGui::Button("Tap tempo")) { mVDSession->tapTempo(); }
			if (ImGui::Button("Time tempo")) { mVDSession->toggleUseTimeWithTempo(); }

			// TODO ImGui::SliderFloat("time x", &mVDAnimation->iTimeFactor, 0.0001f, 1.0f, "%.01f");
			ImGui::SameLine();
			ImGui::PopItemWidth();
		}

#pragma endregion Tempo	

	}
	ImGui::End();

}
