#include "self_tab.h"

namespace SelfTab {
	void Render() {
		if (ImGui::BeginTabItem("Self")) {
			ImGui::Checkbox("Max Vision", &State.MaxVision);
			ImGui::Checkbox("Wallhack", &State.Wallhack);

			if (ImGui::Checkbox("Freecam", &State.FreeCam))
			{
				State.FollowPlayer = false;
				State.PlayerToFollow = **Game::pLocalPlayer;
			}

			SteppedSliderFloat("Freecam Speed", &State.FreeCamSpeed, 0.5f, 3.f, 0.25f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

			if (ImGui::Checkbox("No Clip", &State.NoClip)) {
				if (!IsInGame()) State.NoClip = false;
				else {
					if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
						if (State.NoClip)
							app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
						else
							app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
					}
				}
			}

			ImGui::Checkbox("Reveal Impostors", &State.RevealImpostors);
			ImGui::Checkbox("Unlock Vents", &State.UnlockVents);
			ImGui::Checkbox("Always show Chat Button", &State.ChatAlwaysActive);
			ImGui::Checkbox("Read Messages by Ghosts", &State.ReadGhostMessages);

			ImGui::EndTabItem();
		}
	}
}