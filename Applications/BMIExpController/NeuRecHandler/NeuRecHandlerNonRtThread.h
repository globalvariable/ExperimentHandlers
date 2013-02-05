#ifndef NEU_REC_HANDLER_NON_RT_THREAD_H
#define NEU_REC_HANDLER_NON_RT_THREAD_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
#include "../../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "../../../../BlueSpike/RecordingData.h"
#include "../../../../BlueSpike/SpikeTimeStamp.h"
#include "DataHandling/DataHandling.h"
#include "../../../Library/Messages/TrialHand2NeuRecHand.h"
#include "../../../Library/Messages/NeuRecHand2TrialHand.h"

bool create_neu_rec_handler_non_rt_thread(RtTasksData *arg_rt_tasks_data, RecordingData *arg_recording_data, SpikeTimeStamp *arg_spike_time_stamps, TrialHand2NeuRecHandMsg *arg_msgs_trial_hand_2_neu_rec_hand, GtkWidget *arg_btn_select_directory_to_save);


#endif

