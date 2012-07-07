#include "NeuralNet2MovObjHandSched.h"



bool schedule_neural_net_spikes_to_mov_obj_hand(MovObjData *mov_obj_data, NeuralNet2MovObjHandMsgItem *msg_item, SpikeData *scheduled_spike_data)
{
	if (! write_to_spike_data_with_sorting(scheduled_spike_data, msg_item->layer_num, msg_item->nrn_grp_num, msg_item->neuron_num, msg_item->spike_time+mov_obj_data->neural_net_2_mov_obj_hand_delay))  
		return print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHandSched", "schedule_neural_net_spikes_to_mov_obj_hand", "! write_to_spike_data()");
	return TRUE;
}
