#include "TrialHandParadigm.h"



TrialHandParadigmRobotReach *allocate_trial_hand_paradigm(unsigned int num_of_start_positions, unsigned int num_of_target_positions)
{
	TrialHandParadigmRobotReach *paradigm = g_new0(TrialHandParadigmRobotReach, 1);
	paradigm->start_info.cart_coordinates = g_new0(CartesianCoordinates, num_of_start_positions);
	paradigm->start_info.robot_pulse_widths = g_new0(ThreeDofRobotServoPulse, num_of_start_positions);
	paradigm->start_info.num_of_positions =  num_of_start_positions;

	paradigm->target_info.cart_coordinates = g_new0(CartesianCoordinates, num_of_target_positions);
	paradigm->target_info.robot_pulse_widths = g_new0(ThreeDofRobotServoPulse, num_of_target_positions);
	paradigm->target_info.target_led_comp_idx = g_new0(unsigned int, num_of_target_positions);
	paradigm->target_info.num_of_positions =  num_of_target_positions;

	return paradigm;
}
