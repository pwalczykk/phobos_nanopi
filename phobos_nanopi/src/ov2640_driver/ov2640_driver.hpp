#ifndef OV2640_DRIVER_HPP_
#define OV2640_DRIVER_HPP_

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include "arducam.h"

#define OV2640_CHIPID_HIGH  0x0A
#define OV2640_CHIPID_LOW   0x0B

#define BUF_SIZE (384*1024)

class ov2640_driver{
protected:
    uint8_t buffer[BUF_SIZE];

public:
    ov2640_driver(){}

    void Init(){
        uint8_t vid,pid;
        uint8_t temp;

        for(int i = 0; i < BUF_SIZE; i++) { buffer[i] = 0xFF;}

        wiring_init();
        arducam(smOV2640,CAM1_CS,-1,-1,-1);
        arducam_write_reg(ARDUCHIP_TEST1, 0x55, CAM1_CS);
        temp = arducam_read_reg(ARDUCHIP_TEST1, CAM1_CS);

        if(temp != 0x55) {
            printf("SPI interface error!\n");
            exit(EXIT_FAILURE);
        }
         else{
        	   printf("SPI interface OK!\n");
        	}

        // Change MCU mode
        arducam_write_reg(ARDUCHIP_MODE, 0x00, CAM1_CS);

        // Check if the camera module type is OV2640
        arducam_i2c_read(OV2640_CHIPID_HIGH, &vid);
        arducam_i2c_read(OV2640_CHIPID_LOW, &pid);
        if((vid != 0x26) || (pid != 0x42)) {
            printf("Can't find OV2640 module!\n");
            exit(EXIT_FAILURE);
        } else {
            printf("OV2640 detected\n");
        }

        arducam_set_format(fmtJPEG);
        arducam_init();
        arducam_set_jpeg_size(sz320x240);

        sleep(1); // Let auto exposure do it's thing after changing image settings
    }

    void Capture(){
        // Flush the FIFO
        arducam_flush_fifo(CAM1_CS);
        // Clear the capture done flag
        arducam_clear_fifo_flag(CAM1_CS);
        // Start capture
        // printf("Start capture\n");
        arducam_start_capture(CAM1_CS);
        while (!(arducam_read_reg(ARDUCHIP_TRIG,CAM1_CS) & CAP_DONE_MASK)) ;
        // printf("CAM1 Capture Done\n");

        // printf("Reading FIFO\n");
        size_t len = read_fifo_length(CAM1_CS);
        if (len >= 393216){
  		   printf("Over size.");
  		    exit(EXIT_FAILURE);
  		  }else if (len == 0 ){
  		    printf("Size is 0.");
  		    exit(EXIT_FAILURE);
  		  }
  		  digitalWrite(CAM1_CS,LOW);  //Set CS low
        set_fifo_burst(BURST_FIFO_READ);
        arducam_spi_transfers(buffer,1);//dummy read
        int32_t i=0;
        while(len>4096)
        {
        	arducam_transfers(&buffer[i],4096);
        	len -= 4096;
        	i += 4096;
        }
        arducam_spi_transfers(&buffer[i],len);

        // fwrite(buffer, len+i, 1, fp1);
        digitalWrite(CAM1_CS,HIGH);  //Set CS HIGH
         //Close the file
        delay(100);
        // fclose(fp1);
        // Clear the capture done flag
        arducam_clear_fifo_flag(CAM1_CS);
    }

};

#endif
