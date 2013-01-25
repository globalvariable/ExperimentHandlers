#include "DataFormat_v0.h"


#define META_DATA_FILE_PTR_ARR_IDX		0
#define TRIAL_DATA_FILE_PTR_ARR_IDX		1
#define NUM_OF_DATA_FILE_PER_RECORDING	2


static FILE *file_ptr_arr[NUM_OF_DATA_FILE_PER_RECORDING];

static int create_main_meta_file(char *main_directory_path, TrialHandParadigmRobotReach *paradigm);
static int create_data_files(TimeStamp rec_start, char *data_directory_path);
static int create_meta_data(TimeStamp rec_start, char *data_directory_path);
static int create_trial_data(char *data_directory_path);
static int close_meta_data(TimeStamp rec_end);
static int close_trial_data(TimeStamp rec_end, TrialData *trial_data);
static int delete_data_files(char *data_directory_path);
static int delete_meta_data(char *data_directory_path);
static int delete_trial_data(char *data_directory_path);

int create_main_directory_v0(int num, ...)
{
	FILE *fp;
	char *path_chooser;
  	TrialHandParadigmRobotReach *paradigm;
	DIR	*dir_main_folder;
	char main_directory_path[600];

  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *); 
	paradigm = va_arg ( arguments, TrialHandParadigmRobotReach *); 
	va_end ( arguments );
	
	strcpy(main_directory_path, path_chooser);	
	strcat(main_directory_path, "/RecordTrialHandler");
	if ((dir_main_folder = opendir(main_directory_path)) != NULL)
        {
        	printf ("Recorder: ERROR: path: %s already has RecordTrialHandler folder.\n", path_chooser);		
        	printf ("Recorder: ERROR: Select another folder or delete RecordTrialHandler directory.\n\n");	
		closedir(dir_main_folder );	        		
                return 0;
        }
        closedir(dir_main_folder );
        
	mkdir(main_directory_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

        printf ("TrialHandler: Created /RecordTrialHandler folder in: %s.\n", path_chooser);
        printf ("TrialHandler: /RecordTrialHandler path is: %s.\n", main_directory_path); 
        
	if (!create_main_meta_file(main_directory_path, paradigm))
		return 0;

	if ((fp = fopen("./path_initial_directory", "w")) == NULL)  { printf ("ERROR: Recorder: Couldn't find directory: %s\n\n", "./path_initial_directory"); return 0; }
	fprintf(fp, "%s", path_chooser);
	fclose (fp);		

	return 1;
}

int create_data_directory_v0(int num, ...)
{
	char data_directory_name[10];
	char data_directory_num[10];
	DIR	*dir_data_directory;	
	char *path_chooser;
	char data_directory_path[600];
	TimeStamp rec_start;

	unsigned int i, data_directory_cntr, ret, recording_number;
 
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *); 
	rec_start = va_arg ( arguments, TimeStamp); 
	recording_number = va_arg ( arguments, unsigned int); 
	va_end ( arguments );

	for (i = 0; i < NUM_OF_DATA_FILE_PER_RECORDING; i++)
		file_ptr_arr[i] = NULL;

	data_directory_cntr = recording_number;
	if (data_directory_cntr <10)
	{
		strcpy(data_directory_name, "dat0000");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);
	}
	else if (data_directory_cntr <100)
	{
		strcpy(data_directory_name, "dat000");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}
	else if (data_directory_cntr <1000)
	{
		strcpy(data_directory_name, "dat00");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (data_directory_cntr <10000)
	{
		strcpy(data_directory_name, "dat0");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (data_directory_cntr <100000)
	{
		strcpy(data_directory_name, "dat");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);			
	}	
	else
	{
		printf("Recorder: ERROR: data directory counter is %d.\n", data_directory_cntr);
		printf("Recorder: ERROR: Supported range is 0<= x <100000.\n\n");		
		return 0;
	}
	
	strcpy(data_directory_path, path_chooser);	
	strcat(data_directory_path, "/RecordTrialHandler/");
	strcat(data_directory_path, data_directory_name);	
	if ((dir_data_directory = opendir(data_directory_path)) != NULL)
        {
        	printf ("Recorder: ERROR: path: %s already has %s folder.\n", data_directory_path, data_directory_name);		
		closedir(dir_data_directory);
                return 0;
        }
	closedir(dir_data_directory);	  
      		        
	if ((ret = mkdir(data_directory_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH)) != 0)
	{
		printf("Couldn't makedir: %s\n, Reason: %d\n", data_directory_path, ret);
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "create_data_directory_v0", "mkdir() != 0");
	}	

	if (! create_data_files(rec_start, data_directory_path))
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "create_data_directory_v0", "! create_data_files.");

	return 1;
}

int fclose_all_data_files_v0(int num, ...)
{
	TrialData *trial_data;
	TimeStamp rec_end;

  	va_list arguments;
	va_start ( arguments, num );  
	rec_end = va_arg ( arguments, TimeStamp);  
	trial_data = va_arg ( arguments, TrialData*); 
	va_end ( arguments );	

	if (! close_meta_data(rec_end))
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "create_data_directory_v0", "! close_meta_data");

	if (! close_trial_data(rec_end, trial_data))
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "create_data_directory_v0", "! close_meta_data");

	return 1;
}

int delete_data_directory_v0(int num, ...)   // call it after fclose_all_data_files_v0
{
	char data_directory_name[10];
	char data_directory_num[10];
	DIR	*dir_data_directory;	
	char *path_chooser;
	char data_directory_path[600];

	unsigned int data_directory_cntr, recording_number;
 
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *); 
	recording_number = va_arg ( arguments, unsigned int); 
	va_end ( arguments );

	data_directory_cntr = recording_number;
	if (data_directory_cntr <10)
	{
		strcpy(data_directory_name, "dat0000");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);
	}
	else if (data_directory_cntr <100)
	{
		strcpy(data_directory_name, "dat000");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}
	else if (data_directory_cntr <1000)
	{
		strcpy(data_directory_name, "dat00");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (data_directory_cntr <10000)
	{
		strcpy(data_directory_name, "dat0");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);		
	}	
	else if (data_directory_cntr <100000)
	{
		strcpy(data_directory_name, "dat");
		sprintf(data_directory_num, "%d" , data_directory_cntr);
		strcat(data_directory_name, data_directory_num);			
	}	
	else
	{
		printf("Recorder: ERROR: data directory counter is %d.\n", data_directory_cntr);
		printf("Recorder: ERROR: Supported range is 0<= x <100000.\n\n");		
		return 0;
	}
	
	strcpy(data_directory_path, path_chooser);	
	strcat(data_directory_path, "/RecordTrialHandler/");
	strcat(data_directory_path, data_directory_name);	
	if ((dir_data_directory = opendir(data_directory_path)) == NULL)
        {
        	printf ("Recorder: ERROR: path: %s does not have %s folder.\n", data_directory_path, data_directory_name);		
		closedir(dir_data_directory);
                return 0;
        }
	closedir(dir_data_directory);	 

	if (! delete_data_files(data_directory_path))
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "delete_data_directory_v0", "! delete_data_files(data_directory_path)");

	if (rmdir(data_directory_path) != 0) 
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "delete_data_directory_v0", "! remove(data_directory_path)");

	return 1;
}

int write_to_data_files_v0(int num, ...)
{
	return 1;
}

int write_notes_to_files_v0(int num, ...)
{
	return 1;
}
int write_additional_notes_to_files_v0(int num, ...)
{
	return 1;
}



static int create_main_meta_file(char *main_directory_path, TrialHandParadigmRobotReach *paradigm)
{
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;
	FILE *fp;
	unsigned int i;
 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: TrialHandler: Couldn't create file: %s\n\n", temp_path); return 0; }
		
	fprintf(fp,"----------TrialHandler - Main Meta File----------\n");
	fprintf(fp,"DATA_FORMAT_VERSION\t%d\n", 0);	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"CREATION_DATE\t%s", asctime (timeinfo)); 	// already includes \n
	fprintf(fp,"MAX_TRIAL_LENGTH\t%llu\n", paradigm->max_trial_length); 	
	fprintf(fp,"MIN_TRIAL_REFRACTORY\t%llu\n", paradigm->min_trial_refractory); 	
	fprintf(fp,"MAX_EXTRA_TRIAL_REFRACTORY\t%llu\n", paradigm->max_extra_trial_refractory); 
	fprintf(fp,"NUM_OF_ROBOT_START_POSITIONS\t%u\n", paradigm->num_of_robot_start_positions); 
	fprintf(fp,"NUM_OF_ROBOT_TARGET_POSITIONS\t%u\n", paradigm->num_of_robot_target_positions); 
	fprintf(fp,"NUM_OF_TARGET_LED_COMPONENTS\t%u\n", paradigm->num_of_target_led_components); 
	for (i = 0; i < paradigm->num_of_target_led_components; i++)
		fprintf(fp,"TARGET_LED_COMPONENT_INDEXES_LIST[%u]\t%u\n", i, paradigm->target_led_component_indexes_list[i]); 
	fprintf(fp,"MIN_TARGET_REACH_THRESHOLD->R_X\t%.15f\n", paradigm->min_target_reach_threshold.r_x); 
	fprintf(fp,"MIN_TARGET_REACH_THRESHOLD->R_Y\t%.15f\n", paradigm->min_target_reach_threshold.r_y); 
	fprintf(fp,"MIN_TARGET_REACH_THRESHOLD->R_Z\t%.15f\n", paradigm->min_target_reach_threshold.r_z);
 	fprintf(fp,"MAX_TARGET_REACH_THRESHOLD->R_X\t%.15f\n", paradigm->max_target_reach_threshold.r_x); 
	fprintf(fp,"MAX_TARGET_REACH_THRESHOLD->R_Y\t%.15f\n", paradigm->max_target_reach_threshold.r_y); 
	fprintf(fp,"MAX_TARGET_REACH_THRESHOLD->R_Z\t%.15f\n", paradigm->max_target_reach_threshold.r_z);
	fprintf(fp,"TARGET_REACH_THRESHOLD_CHANGE_RATE\t%.15f\n", paradigm->target_reach_threshold_change_rate);

	fprintf(fp,"----------TrialHandler - End of Main Meta File----------\n");
	fclose(fp);
	return 1;
}

static int create_data_files(TimeStamp rec_start, char *data_directory_path)
{
	if (!create_meta_data(rec_start, data_directory_path))
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "create_data_files", "! create_meta_data");
	
	if (!create_trial_data(data_directory_path))
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "create_data_files", "! create_trial_data");
	
	return 1;
}

static int create_meta_data(TimeStamp rec_start, char *data_directory_path)
{
	char temp[600];
	FILE *fp;
	time_t rawtime;
	struct tm * timeinfo;
		
	strcpy(temp, data_directory_path);
	strcat(temp, "/meta");
	if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: TrialHandler: Couldn't create file: %s\n\n", temp); return 0; }
	fprintf(fp,"----------TrialHandler - Meta File----------\n");
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"RECORDING START\t%llu\n", rec_start);		
	file_ptr_arr[META_DATA_FILE_PTR_ARR_IDX] = fp;


	return 1;	
}

static int create_trial_data(char *data_directory_path)
{
	char temp[600];
	FILE *fp;
		
	strcpy(temp, data_directory_path);
	strcat(temp, "/trial_data");
	if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: TrialHandler: Couldn't create file: %s\n\n", temp); return 0; }
	fprintf(fp,"----------TrialHandler - TrialData File----------\n");

	file_ptr_arr[TRIAL_DATA_FILE_PTR_ARR_IDX] =  fp;

	return 1;	
}

static int close_meta_data(TimeStamp rec_end)
{
	FILE *fp = file_ptr_arr[META_DATA_FILE_PTR_ARR_IDX];
	fprintf(fp,"RECORDING END\t%llu\n", rec_end);	
	fprintf(fp,"----------TrialHandler - End of Meta File----------\n");
	fclose(fp);
	return 1;
}

static int close_trial_data(TimeStamp rec_end, TrialData *trial_data)
{
	FILE *fp = file_ptr_arr[TRIAL_DATA_FILE_PTR_ARR_IDX];

	fprintf(fp,"trial_start_time\t%llu\n", trial_data->trial_start_time);
	fprintf(fp,"trial_end_time\t%llu\n", trial_data->trial_end_time);
	fprintf(fp,"trial_length\t%llu\n", trial_data->trial_length);
	fprintf(fp,"target_led_component_list_idx\t%u\n", trial_data->target_led_component_list_idx);
	fprintf(fp,"robot_start_position_idx\t%u\n", trial_data->robot_start_position_idx);
	fprintf(fp,"robot_target_position_idx\t%u\n", trial_data->robot_target_position_idx);
	fprintf(fp,"reward_magnitude\t%.15f\n", trial_data->reward_magnitude);
	fprintf(fp,"binary_reward\t%u\n", trial_data->binary_reward);
	fprintf(fp,"binary_reward_windowed_average\t%.15f\n", trial_data->binary_reward_windowed_average);
	fprintf(fp,"trial_length_windowed_average\t%llu\n", trial_data->trial_length_windowed_average);
	fprintf(fp,"remained_distance_to_target\t%.15f\n", trial_data->remained_distance_to_target);
	fprintf(fp,"initial_distance_to_target\t%.15f\n", trial_data->initial_distance_to_target);
	fprintf(fp,"rewarding_threshold.r_x\t%.15f\n", trial_data->rewarding_threshold.r_x);
	fprintf(fp,"rewarding_threshold.r_y\t%.15f\n", trial_data->rewarding_threshold.r_y);
	fprintf(fp,"rewarding_threshold.r_z\t%.15f\n", trial_data->rewarding_threshold.r_z);
	fprintf(fp,"gui_selected_target_position_idx\t%u\n", trial_data->gui_selected_target_position_idx);
	fprintf(fp,"auto_target_select_mode_on\t%u\n", trial_data->auto_target_select_mode_on);

	fprintf(fp,"----------TrialHandler - End of TrialData File----------\n");
	fclose(fp);
	return 1;
}


static int delete_data_files(char *data_directory_path)
{
	if (! delete_meta_data(data_directory_path))
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "delete_data_files_v0", "! delete_meta_data(data_directory_path)");
	
	if (! delete_trial_data(data_directory_path))
		return print_message(ERROR_MSG ,"TrialHandler", "DataFormat_v0", "delete_data_files_v0", "! delete_trial_data(data_directory_path)");

	return 1;
}

static int delete_meta_data(char *data_directory_path)
{
	char temp[600];
		
	strcpy(temp, data_directory_path);
	strcat(temp, "/meta");
	
	if (remove(temp) != 0)  { printf ("ERROR: TrialHandler: Couldn't delete file: %s\n\n", temp); return 0; }

	return 1;	
}

static int delete_trial_data(char *data_directory_path)
{
	char temp[600];

	strcpy(temp, data_directory_path);
	strcat(temp, "/trial_data");	
	if (remove(temp) != 0)  { printf ("ERROR: TrialHandler: Couldn't delete file: %s\n\n", temp); return 0; }

	return 1;	
}
