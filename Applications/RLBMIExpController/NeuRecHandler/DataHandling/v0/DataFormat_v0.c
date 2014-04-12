#include "DataFormat_v0.h"

static unsigned int recording_data_buff_read_start_idx[MAX_NUM_OF_MWA][MAX_NUM_OF_CHAN_PER_MWA];
static unsigned int recording_data_buff_read_end_idx[MAX_NUM_OF_MWA][MAX_NUM_OF_CHAN_PER_MWA];
static unsigned int spike_time_stamp_buff_read_start_idx[MAX_NUM_OF_MWA][MAX_NUM_OF_CHAN_PER_MWA];
static unsigned int spike_time_stamp_buff_read_end_idx[MAX_NUM_OF_MWA][MAX_NUM_OF_CHAN_PER_MWA];

static FILE *meta_data_file_ptr;
static FILE *recording_data_file_ptr_arr[MAX_NUM_OF_MWA][MAX_NUM_OF_CHAN_PER_MWA];
static FILE *spike_time_stamps_file_ptr[MAX_NUM_OF_MWA][MAX_NUM_OF_CHAN_PER_MWA];

static int create_main_meta_file(char *main_directory_path);
static int create_data_files(TimeStamp rec_start, char *data_directory_path);
static int create_meta_data(TimeStamp rec_start, char *data_directory_path);
static int create_recording_data(char *data_directory_path);
static int create_spike_time_stamps_data(char *data_directory_path);
static int write_to_recording_data(RecordingData *recording_data);
static int write_to_spike_time_stamps_data(SortedSpikes *bluespike_sorted_spikes);
static int close_meta_data(TimeStamp rec_end);
static int close_recording_data(RecordingData *recording_data);
static int close_spike_time_stamps_data(SortedSpikes *bluespike_sorted_spikes);
static int delete_data_files(char *data_directory_path);
static int delete_meta_data(char *data_directory_path);
static int delete_recording_data(char *data_directory_path);
static int delete_spike_time_stamps_data(char *data_directory_path);

int create_main_directory_v0(int num, ...)
{
	FILE *fp;
	char *path_chooser;
	DIR	*dir_main_folder;
	char main_directory_path[600];

  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *); 
	va_end ( arguments );
	
	strcpy(main_directory_path, path_chooser);	
	strcat(main_directory_path, "/NeuRecHandlerRecord");
	if ((dir_main_folder = opendir(main_directory_path)) != NULL)
        {
        	printf ("NeuRecHandler: ERROR: path: %s already has NeuRecHandlerRecord folder.\n", path_chooser);		
        	printf ("NeuRecHandler: ERROR: Select another folder or delete NeuRecHandlerRecord directory.\n\n");	
		closedir(dir_main_folder );	        		
                return 0;
        }
        closedir(dir_main_folder );
        
	mkdir(main_directory_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

        printf ("NeuRecHandler: Created /NeuRecHandlerRecord folder in: %s.\n", path_chooser);
        printf ("NeuRecHandler: /NeuRecHandlerRecord path is: %s.\n", main_directory_path); 
        
	if (!create_main_meta_file(main_directory_path))
		return 0;

	if ((fp = fopen("./path_initial_directory", "w")) == NULL)  { printf ("ERROR: NeuRecHandler: Couldn't find directory: %s\n\n", "./path_initial_directory"); return 0; }
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
	TimeStamp rec_start, recording_start_time;
	RecordingData *recording_data;
	SortedSpikes *bluespike_sorted_spikes;

	unsigned int i, j, data_directory_cntr, ret, recording_number;
 
  	va_list arguments;
	va_start ( arguments, num );   
    	path_chooser = va_arg ( arguments, char *); 
	rec_start = va_arg ( arguments, TimeStamp); 
	recording_number = va_arg ( arguments, unsigned int); 
	recording_data = va_arg ( arguments, RecordingData *); 
	bluespike_sorted_spikes = va_arg ( arguments, SortedSpikes *); 
	va_end ( arguments );

	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			recording_data_buff_read_start_idx[i][j] = (*recording_data)[i][j].buff_idx_write;
			spike_time_stamp_buff_read_start_idx[i][j]  = (*bluespike_sorted_spikes)[i][j].buff_idx_write;
		}
	}

	recording_start_time = rec_start;		//  ACCORDING TO THIS DESIGN, RECORDING START TIME AND THE CORRESPONDING NEURAL DATA SAMPLE MIGHT NOT COINCODE TO SAME TIME BUT THEY WILL BE ALMOST EQUAL. 

	meta_data_file_ptr = NULL;
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			recording_data_file_ptr_arr[i][j] = NULL;
			spike_time_stamps_file_ptr[i][j] = NULL;
		}
	}


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
		printf("NeuRecHandler: ERROR: data directory counter is %d.\n", data_directory_cntr);
		printf("NeuRecHandler: ERROR: Supported range is 0<= x <100000.\n\n");		
		return 0;
	}
	
	strcpy(data_directory_path, path_chooser);	
	strcat(data_directory_path, "/NeuRecHandlerRecord/");
	strcat(data_directory_path, data_directory_name);	
	if ((dir_data_directory = opendir(data_directory_path)) != NULL)
        {
        	printf ("NeuRecHandler: ERROR: path: %s already has %s folder.\n", data_directory_path, data_directory_name);		
		closedir(dir_data_directory);
                return 0;
        }
	closedir(dir_data_directory);	  
      		        
	if ((ret = mkdir(data_directory_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH)) != 0)
	{
		printf("Couldn't makedir: %s\n, Reason: %d\n", data_directory_path, ret);
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "create_data_directory_v0", "mkdir() != 0");
	}	

	if (! create_data_files(recording_start_time, data_directory_path))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "create_data_directory_v0", "! create_data_files.");
	return 1;
}
int fclose_all_data_files_v0(int num, ...)
{
	TimeStamp rec_end, recording_end_time;
	RecordingData *recording_data;
	SortedSpikes *bluespike_sorted_spikes;
	unsigned int i, j;
  	va_list arguments;
	va_start ( arguments, num );   
	rec_end = va_arg ( arguments, TimeStamp); 
	recording_data = va_arg ( arguments, RecordingData *); 
	bluespike_sorted_spikes = va_arg ( arguments, SortedSpikes *); 
	va_end ( arguments );


	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			recording_data_buff_read_end_idx[i][j] = (*recording_data)[i][j].buff_idx_write;
			spike_time_stamp_buff_read_end_idx[i][j]  = (*bluespike_sorted_spikes)[i][j].buff_idx_write;
		}
	}
	recording_end_time = rec_end;

	if (! close_meta_data(recording_end_time))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "create_data_directory_v0", "! close_meta_data");

	if (! close_recording_data(recording_data))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "create_data_directory_v0", "! close_recording_data");

	if (! close_spike_time_stamps_data(bluespike_sorted_spikes))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "create_data_directory_v0", "! close_spike_time_stamps_data");

	return 1;
}

int delete_data_directory_v0(int num, ...)
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
		printf("NeuRecHandler: ERROR: data directory counter is %d.\n", data_directory_cntr);
		printf("NeuRecHandler: ERROR: Supported range is 0<= x <100000.\n\n");		
		return 0;
	}
	
	strcpy(data_directory_path, path_chooser);	
	strcat(data_directory_path, "/NeuRecHandlerRecord/");
	strcat(data_directory_path, data_directory_name);	
	if ((dir_data_directory = opendir(data_directory_path)) == NULL)
        {
        	printf ("NeuRecHandler: ERROR: path: %s does not have %s folder.\n", data_directory_path, data_directory_name);		
		closedir(dir_data_directory);
                return 0;
        }
	closedir(dir_data_directory);	 

	if (! delete_data_files(data_directory_path))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "delete_data_directory_v0", "! delete_data_files(data_directory_path)");

	if (rmdir(data_directory_path) != 0) 
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "delete_data_directory_v0", "! remove(data_directory_path)");
	return 1;
}

int write_to_data_files_v0(int num, ...)
{
	RecordingData *recording_data;
	SortedSpikes *bluespike_sorted_spikes;

  	va_list arguments;
	va_start ( arguments, num );   
    	recording_data = va_arg ( arguments, RecordingData*); 
    	bluespike_sorted_spikes = va_arg ( arguments, SortedSpikes*); 
	va_end ( arguments );

	if (! write_to_recording_data(recording_data))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "write_to_data_files_v0", "! write_to_recording_data()");

	if (! write_to_spike_time_stamps_data(bluespike_sorted_spikes))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "write_to_data_files_v0", "! write_to_spike_time_stamps_data()");

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



static int create_main_meta_file(char *main_directory_path)
{
	char  temp_path[600];
	time_t rawtime;
	struct tm * timeinfo;
	FILE *fp;

 	strcpy(temp_path, main_directory_path);
 	strcat(temp_path, "/meta");
	if ((fp = fopen(temp_path, "w")) == NULL)  { printf ("ERROR: NeuRecHandler: Couldn't create file: %s\n\n", temp_path); return 0; }
		
	fprintf(fp,"----------NeuRecHandler - Main Meta File----------\n");
	fprintf(fp,"DATA_FORMAT_VERSION\t%d\n", 0);	
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"CREATION_DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"MAX_NUM_OF_MWA\t%d\n", MAX_NUM_OF_MWA);
	fprintf(fp,"MAX_NUM_OF_CHAN_PER_MWA\t%d\n",MAX_NUM_OF_CHAN_PER_MWA);
	fprintf(fp,"MAX_NUM_OF_UNIT_PER_CHAN\t%d\n",MAX_NUM_OF_UNIT_PER_CHAN);
	fprintf(fp,"NUM_OF_SAMP_PER_SPIKE\t%d\n",NUM_OF_SAMP_PER_SPIKE);
	fprintf(fp,"MAX_NUM_OF_DAQ_CARD\t%d\n",MAX_NUM_OF_DAQ_CARD);
	fprintf(fp,"MAX_NUM_OF_CHANNEL_PER_DAQ_CARD\t%d\n",MAX_NUM_OF_CHANNEL_PER_DAQ_CARD);	
	fprintf(fp,"SAMPLING_INTERVAL\t%d\tNANOSECONDS\n", SAMPLING_INTERVAL);
	fprintf(fp,"LOWEST_VOLTAGE_MV\t%f\tMILLIVOLTS\n",LOWEST_VOLTAGE_MV);
	fprintf(fp,"HIGHEST_VOLTAGE_MV\t%f\tMILLIVOLTS\n",HIGHEST_VOLTAGE_MV);	
	fprintf(fp,"DAQ_0_MODEL\t%s\n",DAQ_0_MODEL);	
	fprintf(fp,"typedef float RecordingDataSample;\n");
	fprintf(fp,"sizeof(RecordingDataSample)\t%lu\n", sizeof(RecordingDataSample));	
	fprintf(fp,"typedef struct __SpikeTimeStampItem\n");
	fprintf(fp,"{\n");
	fprintf(fp,"TimeStamp 		peak_time;\n");
	fprintf(fp,"unsigned int		mwa_or_layer;\n");
	fprintf(fp,"unsigned int		channel_or_neuron_group;\n");
	fprintf(fp,"unsigned int		unit_or_neuron;\n");
	fprintf(fp,"} SortedSpikeItem;\n");
	fprintf(fp,"sizeof(SortedSpikeItem)\t%lu\n", sizeof(SortedSpikeItem));
	fprintf(fp,"----------NeuRecHandler - End of Main Meta File----------\n");
	fclose(fp);
	return 1;
}

static int create_data_files(TimeStamp rec_start, char *data_directory_path)
{
	if (!create_meta_data(rec_start, data_directory_path))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "create_data_files", "! create_meta_data");
	
	if (!create_recording_data(data_directory_path))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "create_data_files", "! create_recording_data");

	if (!create_spike_time_stamps_data(data_directory_path))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "create_data_files", "! create_spike_time_stamps_data");

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
	if ((fp = fopen(temp, "w")) == NULL)  { printf ("ERROR: NeuRecHandler: Couldn't create file: %s\n\n", temp); return 0; }
	fprintf(fp,"----------NeuRecHandler - Meta File----------\n");
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	fprintf(fp,"DATE\t%s", asctime (timeinfo)); 	
	fprintf(fp,"RECORDING START\t%llu\n", rec_start);		
	meta_data_file_ptr = fp;


	return 1;	
}

static int create_recording_data(char *data_directory_path)
{
	char temp[600];
	FILE *fp;
	char char_mwa_num[20], char_chan_num[20];
	unsigned int i,j;
	
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			strcpy(temp, data_directory_path);	
			if (i<10)
			{
				sprintf(char_mwa_num, "/rec_mwa_0%u" , i);
				strcat(temp, char_mwa_num);
			}
			else if (i<100)
			{
				sprintf(char_mwa_num, "/rec_mwa_%u" , i);
				strcat(temp, char_mwa_num);				
			}
			else
			{
				printf ("ERROR: NeuRecHandler: MAX MWA NUM is larger than 99\n\n");
				printf ("ERROR: NeuRecHandler: Couldn't create all recording files requested\n\n");
				return 0; 
			}
			strcat(temp, "_");
			if (j<10)
			{
				sprintf(char_chan_num, "chan_00%u" , j);
				strcat(temp, char_chan_num);
			}
			else if (j<100)
			{
				sprintf(char_chan_num, "chan_0%u" , j);
				strcat(temp, char_chan_num);				
			}
			else if (j<1000)
			{
				sprintf(char_chan_num, "chan_%u" , j);
				strcat(temp, char_chan_num);			
			}
			else
			{
				printf ("ERROR: NeuRecHandler: MAX NUM OF CHAN PER MWA is larger than 999\n\n");
				printf ("ERROR: NeuRecHandler: Couldn't create all recording files requested\n\n");
				return 0; 
			}			
			if ((fp = fopen(temp, "wb")) == NULL)  { printf ("ERROR: NeuRecHandler: Couldn't create file: %s\n\n", temp); return 0; }
			recording_data_file_ptr_arr[i][j] =  fp;
		}
	}

	return 1;
}

static int create_spike_time_stamps_data(char *data_directory_path)
{
	char temp[600];
	FILE *fp;
	char char_mwa_num[20], char_chan_num[20];
	unsigned int i,j;
	
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			strcpy(temp, data_directory_path);	
			if (i<10)
			{
				sprintf(char_mwa_num, "/spikes_mwa_0%u" , i);
				strcat(temp, char_mwa_num);
			}
			else if (i<100)
			{
				sprintf(char_mwa_num, "/spikes_mwa_%u" , i);
				strcat(temp, char_mwa_num);				
			}
			else
			{
				printf ("ERROR: BlueSpike: MAX MWA NUM is larger than 99\n\n");
				printf ("ERROR: BlueSpike: Couldn't create all spike files requested\n\n");
				return 0; 
			}
			strcat(temp, "_");
			if (j<10)
			{
				sprintf(char_chan_num, "chan_00%u" , j);
				strcat(temp, char_chan_num);
			}
			else if (j<100)
			{
				sprintf(char_chan_num, "chan_0%u" , j);
				strcat(temp, char_chan_num);				
			}
			else if (j<1000)
			{
				sprintf(char_chan_num, "chan_%u" , j);
				strcat(temp, char_chan_num);			
			}
			else
			{
				printf ("ERROR: BlueSpike: MAX NUM OF CHAN PER MWA is larger than 999\n\n");
				printf ("ERROR: BlueSpike: Couldn't create all recording files requested\n\n");
				return 0; 
			}			
			if ((fp = fopen(temp, "wb")) == NULL)  { printf ("ERROR: BlueSpike: Couldn't create file: %s\n\n", temp); return 0; }
			spike_time_stamps_file_ptr[i][j] =  fp;
		}
	}

	return 1;
}

static int write_to_recording_data(RecordingData *recording_data)
{
	RecordingDataSample	*recording_data_chan_buff;
	FILE *fp;
	unsigned int i,j, idx, end_idx;
	RecordingDataSampleFloat sample;
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			recording_data_chan_buff = (*recording_data)[i][j].rec_data_buff;
			idx = recording_data_buff_read_start_idx[i][j];
			end_idx = (*recording_data)[i][j].buff_idx_write;
			fp = recording_data_file_ptr_arr[i][j];
			while (idx != end_idx)
			{
				sample = (RecordingDataSampleFloat)(recording_data_chan_buff[idx]);	// lower the precision for faster writing
				fwrite(&sample, sizeof(RecordingDataSampleFloat), 1, fp);
				idx++;	
				if (idx ==	RECORDING_DATA_BUFF_SIZE)
					idx = 0;	
			}
			recording_data_buff_read_start_idx[i][j] = end_idx;
		}
	}		
	return 1;

}
static int write_to_spike_time_stamps_data(SortedSpikes *bluespike_sorted_spikes)
{
	SortedSpikeItem	*sorted_spike_buff;
	FILE *fp;
	unsigned int i,j, idx, end_idx;
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			sorted_spike_buff = (*bluespike_sorted_spikes)[i][j].buffer;
			idx = spike_time_stamp_buff_read_start_idx[i][j];
			end_idx = (*bluespike_sorted_spikes)[i][j].buff_idx_write;
			fp = spike_time_stamps_file_ptr[i][j];
			while (idx != end_idx)
			{
				fwrite(&(sorted_spike_buff[idx]), sizeof(SortedSpikeItem), 1, fp);
				idx++;	
				if (idx ==	BLUESPIKE_SORTED_SPIKE_BUFF_SIZE)
					idx = 0;	
			}
			spike_time_stamp_buff_read_start_idx[i][j] = end_idx;
		}
	}		
	return 1;
}

static int close_meta_data(TimeStamp rec_end)
{
	fprintf(meta_data_file_ptr,"RECORDING END\t%llu\n", rec_end);	
	fprintf(meta_data_file_ptr,"----------NeuRecHandler - End of Meta File----------\n");
	fclose(meta_data_file_ptr);
	return 1;
}

static int close_recording_data(RecordingData *recording_data)
{
	RecordingDataSample	*recording_data_chan_buff;
	FILE *fp;
	unsigned int i,j, idx, end_idx;
	RecordingDataSampleFloat sample;
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			recording_data_chan_buff = (*recording_data[i][j]).rec_data_buff;
			idx = recording_data_buff_read_start_idx[i][j];
			end_idx = recording_data_buff_read_end_idx[i][j];	// before closing the files, write data up to the write indexes of the buffers determined by fclose_all_data_files_v0()
			fp = recording_data_file_ptr_arr[i][j];
			while (idx != end_idx)
			{
				sample = (RecordingDataSampleFloat)(recording_data_chan_buff[idx]);	// lower the precision for faster writing
				fwrite(&sample, sizeof(RecordingDataSampleFloat), 1, fp);
				idx++;	
				if (idx ==	RECORDING_DATA_BUFF_SIZE)
					idx = 0;	
			}
			fclose(fp);
		}
	}	
	return 1;
}
static int close_spike_time_stamps_data(SortedSpikes *bluespike_sorted_spikes)
{
	SortedSpikeItem	*sorted_spike_buff;
	FILE *fp;
	unsigned int i,j, idx, end_idx;
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			sorted_spike_buff = (*bluespike_sorted_spikes)[i][j].buffer;
			idx = spike_time_stamp_buff_read_start_idx[i][j];
			end_idx = (*bluespike_sorted_spikes)[i][j].buff_idx_write;
			fp = spike_time_stamps_file_ptr[i][j];
			while (idx != end_idx)
			{
				fwrite(&(sorted_spike_buff[idx]), sizeof(SortedSpikeItem), 1, fp);
				idx++;	
				if (idx ==	BLUESPIKE_SORTED_SPIKE_BUFF_SIZE)
					idx = 0;	
			}
			fclose(fp);
		}
	}		

	return 1;
}

static int delete_data_files(char *data_directory_path)
{
	if (! delete_meta_data(data_directory_path))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "delete_data_files", "! delete_meta_data(data_directory_path)");
	
	if (! delete_recording_data(data_directory_path))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "delete_data_files", "! delete_delete_recording_data(data_directory_path)");

	if (! delete_spike_time_stamps_data(data_directory_path))
		return print_message(ERROR_MSG ,"NeuRecHandler", "DataFormat_v0", "delete_data_files", "! delete_spike_time_stamps_data(data_directory_path)");

	return 1;
}

static int delete_meta_data(char *data_directory_path)
{
	char temp[600];
		
	strcpy(temp, data_directory_path);
	strcat(temp, "/meta");
	
	if (remove(temp) != 0)  { printf ("ERROR: NeuRecHandler: Couldn't delete file: %s\n\n", temp); return 0; }

	return 1;
}

static int delete_recording_data(char *data_directory_path)
{
	char temp[600];
	char char_mwa_num[20], char_chan_num[20];
	unsigned int i,j;
	
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j=0; j<MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			strcpy(temp, data_directory_path);	
			if (i<10)
			{
				sprintf(char_mwa_num, "/rec_mwa_0%u" , i);
				strcat(temp, char_mwa_num);
			}
			else if (i<100)
			{
				sprintf(char_mwa_num, "/rec_mwa_%u" , i);
				strcat(temp, char_mwa_num);				
			}
			else
			{
				printf ("ERROR: NeuRecHandler: MAX MWA NUM is larger than 99\n\n");
				printf ("ERROR: NeuRecHandler: Couldn't create all recording files requested\n\n");
				return 0; 
			}
			strcat(temp, "_");
			if (j<10)
			{
				sprintf(char_chan_num, "chan_00%u" , j);
				strcat(temp, char_chan_num);
			}
			else if (j<100)
			{
				sprintf(char_chan_num, "chan_0%u" , j);
				strcat(temp, char_chan_num);				
			}
			else if (j<1000)
			{
				sprintf(char_chan_num, "chan_%u" , j);
				strcat(temp, char_chan_num);			
			}
			else
			{
				printf ("ERROR: NeuRecHandler: MAX NUM OF CHAN PER MWA is larger than 999\n\n");
				printf ("ERROR: NeuRecHandler: Couldn't create all recording files requested\n\n");
				return 0; 
			}	
			if (remove(temp) != 0)  { printf ("ERROR: NeuRecHandler: Couldn't delete file: %s\n\n", temp); return 0; }
		}
	}
	return 1;
}
static int delete_spike_time_stamps_data(char *data_directory_path)
{
	char temp[600];
		
	strcpy(temp, data_directory_path);
	strcat(temp, "/spikes");
	
	if (remove(temp) != 0)  { printf ("ERROR: NeuRecHandler: Couldn't delete file: %s\n\n", temp); return 0; }

	return 1;
}

