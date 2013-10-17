/* PointCloudSample_publisher.cxx

   A publication of data of type rapid::PointCloudSample

   This file is derived from code automatically generated by the rtiddsgen 
   command:

   rtiddsgen -language C++ -example <arch> PointCloudSample.idl

   Example publication of type rapid::PointCloudSample automatically generated by 
   'rtiddsgen'. To test them follow these steps:

   (1) Compile this file and the example subscription.

   (2) Start the subscription on the same domain used for RTI Data Distribution
       with the command
       objs/<arch>/PointCloudSample_subscriber <domain_id> <sample_count>
                
   (3) Start the publication on the same domain used for RTI Data Distribution
       with the command
       objs/<arch>/PointCloudSample_publisher <domain_id> <sample_count>

   (4) [Optional] Specify the list of discovery initial peers and 
       multicast receive addresses via an environment variable or a file 
       (in the current working directory) called NDDS_DISCOVERY_PEERS. 
       
   You can run any number of publishers and subscribers programs, and can 
   add and remove them dynamically from the domain.

                                   
   Example:
        
       To run the example application on domain <domain_id>:
                          
       On Unix: 
       
       objs/<arch>/PointCloudSample_publisher <domain_id> o
       objs/<arch>/PointCloudSample_subscriber <domain_id> 
                            
       On Windows:
       
       objs\<arch>\PointCloudSample_publisher <domain_id>  
       objs\<arch>\PointCloudSample_subscriber <domain_id>    

       
modification history
------------ -------       
*/

#include <stdio.h>
#include <stdlib.h>
#ifdef RTI_VX653
#include <vThreadsData.h>
#endif
#include "PointCloudSample.h"
#include "PointCloudSampleSupport.h"
#include "PointCloudConfig.h"
#include "PointCloudConfigSupport.h"
#include "ndds/ndds_cpp.h"

#include "ndds/ndds_namespace_cpp.h"

#include <math.h>
#include <sys/time.h>

static const char* agent = "Centaur2";

using namespace DDS;

/* Delete all entities */
static int publisher_shutdown(DomainParticipant *participant)
{
    ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = participant->delete_contained_entities();
        if (retcode != RETCODE_OK) {
            printf("delete_contained_entities error %d\n", retcode);
            status = -1;
        }

        retcode = TheParticipantFactory->delete_participant(participant);
        if (retcode != RETCODE_OK) {
            printf("delete_participant error %d\n", retcode);
            status = -1;
        }
    }
    return status;
}

/**
 * populate header
 */ 
void setHeader(rapid::Header& header) {
  strcpy(header.srcName, "this");
  strcpy(header.assetName, agent);
  struct timeval tp;
  gettimeofday(&tp, NULL);
  header.timeStamp  = ((long long)tp.tv_sec*1000000L)+tp.tv_usec;
  header.statusCode = 0;
  header.serial     = 0;
}

/**
 * create point cloud config
 */ 
void setPointCloudConfig(rapid::PointCloudConfig& config) 
{
  setHeader(config.hdr);
  strcpy(config.frameName, "frame");
  config.xyzMode = rapid::PS_XYZ;
}

/**
 * fill the point cloud sample with some values
 */
void updatePointCloudSample(rapid::PointCloudSample& sample, int numPoints, double offset) 
{
  setHeader(sample.hdr);
  sample.origin[0] = 0;
  sample.origin[1] = offset;
  sample.origin[2] = 0;
  sample.xyzScale[0] = 0.1;
  sample.xyzScale[1] = 0.1;
  sample.xyzScale[2] = 0.1;
  sample.points.length(numPoints);
  for(int i = 0; i < numPoints; i++) {
    int add1 = (sample.hdr.timeStamp-i*500)/100000;
    int add2 = (sample.hdr.timeStamp-i*100)/250000;
    rapid::PointSample& s = sample.points[i];
    s.xyz[0] = i/100;
    s.xyz[1] = i%100;
    s.xyz[2] = (short)( 10*sin((add1+s.xyz[0])*0.1) + 10*sin((add2+s.xyz[1])*0.13)) ;
    s.attributes[0] = 0;
    s.attributes[1] = 0;
  }
}

/**
 * create a generic data writer
 */
DataWriter* createDataWriter(const char* topicName, const char* typeName, 
                             const char* qosLibrary, const char* qosProfile, 
                             Topic*& topic,
                             Publisher* publisher,
                             DomainParticipant* participant)
{
    DataWriter* writer = NULL;
    fprintf(stderr, "topicName=%s\n", topicName);
    fprintf(stderr, " typeName=%s\n", typeName);
    topic = participant->create_topic(
        topicName,
        typeName, 
        TOPIC_QOS_DEFAULT, 
        NULL, 
        STATUS_MASK_NONE);
        
    if (topic == NULL) {
        printf("create_topic error\n");
        publisher_shutdown(participant);
        exit(-1);
    }

    writer = publisher->create_datawriter_with_profile(
        topic, 
        qosLibrary, 
        qosProfile,
        NULL,
        STATUS_MASK_NONE);
        
    if (writer == NULL) {
        printf("create_datawriter error\n");
        publisher_shutdown(participant);
        exit(-1);
    }
    return writer;
}


/**
 *
 */
//=================================================================================
extern "C" int publisher_main(int domainId, int sample_count)
{
    DomainParticipant *participant      = NULL;
    Publisher  *publisher               = NULL;
    DataWriter *writer                  = NULL;
    
    const char* qosLibrary              = "Centaur2QosLibrary";
    
    const char* topicNameAAC             = "rapid_pointcloud_config";
    const char* qosProfileAAC            = "RapidPointCloudConfigProfile";
    Topic* topicAAC                      = NULL;
    InstanceHandle_t instanceHandleAAC   = HANDLE_NIL;
    rapid::PointCloudConfig* instanceAAC = NULL;
    rapid::PointCloudConfigDataWriter*  rapid_PointCloudConfig_writerAAC = NULL;
    
    const char* topicNameBBC             = "rapid_pointcloud_config-debug";
    const char* qosProfileBBC            = "RapidPointCloudConfigProfile";
    Topic* topicBBC                      = NULL;
    InstanceHandle_t instanceHandleBBC   = HANDLE_NIL;
    rapid::PointCloudConfig* instanceBBC = NULL;
    rapid::PointCloudConfigDataWriter*  rapid_PointCloudConfig_writerBBC = NULL;
    
    const char* topicNameAAS             = "rapid_pointcloud_sample";
    const char* qosProfileAAS            = "RapidPointCloudSampleProfile";
    Topic* topicAAS                      = NULL;
    InstanceHandle_t instanceHandleAAS   = HANDLE_NIL;
    rapid::PointCloudSample* instanceAAS = NULL;
    rapid::PointCloudSampleDataWriter*  rapid_PointCloudSample_writerAAS = NULL;
    
    const char* topicNameBBS             = "rapid_pointcloud_sample-debug";
    const char* qosProfileBBS            = "RapidPointCloudSampleProfile";
    Topic* topicBBS                      = NULL;
    InstanceHandle_t instanceHandleBBS   = HANDLE_NIL;
    rapid::PointCloudSample* instanceBBS = NULL;
    rapid::PointCloudSampleDataWriter*  rapid_PointCloudSample_writerBBS = NULL;
    
    ReturnCode_t retcode;
    
    const char* typeName = NULL;
    int         count = 0;  
    Duration_t  send_period = {0,500000000};

    /* To customize participant Qos, use the configuration file USER_QOS_PROFILES.xml */
    participant = TheParticipantFactory->create_participant(
        domainId, PARTICIPANT_QOS_DEFAULT, 
        NULL, STATUS_MASK_NONE);
    if (participant == NULL) {
        printf("create_participant error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* To customize publisher Qos, use the configuration file USER_QOS_PROFILES.xml */
    PublisherQos* qos = new PublisherQos();
    participant->get_default_publisher_qos(*qos);
    qos->partition.name.ensure_length(1,1);
    qos->partition.name[0] = DDS_String_dup(agent);
    publisher = participant->create_publisher(*qos, NULL, STATUS_MASK_NONE);
    if (publisher == NULL) {
        printf("create_publisher error\n");
        publisher_shutdown(participant);
        return -1;
    }

    /* Register type before creating topic */
    retcode = rapid::PointCloudConfigTypeSupport::register_type( participant, rapid::PointCloudConfigTypeSupport::get_type_name());
    fprintf(stderr, "register_type retcode = %d\n", retcode);
    retcode = rapid::PointCloudSampleTypeSupport::register_type( participant, rapid::PointCloudSampleTypeSupport::get_type_name());
    fprintf(stderr, "register_type retcode = %d\n", retcode);

    //=== Create Publication AAS =============================
    fprintf(stderr, "*** Create PointCloudSample\n------------------------------\n");
    typeName = rapid::PointCloudSampleTypeSupport::get_type_name();
    writer   = createDataWriter(topicNameAAS, typeName, qosLibrary, qosProfileAAS, topicAAS, publisher, participant);
    rapid_PointCloudSample_writerAAS = rapid::PointCloudSampleDataWriter::narrow(writer);
    instanceAAS = rapid::PointCloudSampleTypeSupport::create_data();
    setHeader(instanceAAS->hdr);
    instanceHandleAAS = rapid_PointCloudSample_writerAAS->register_instance(*instanceAAS);

    //=== Create Publication BBS =============================
    fprintf(stderr, "*** Create PointCloudSample\n------------------------------\n");
    typeName = rapid::PointCloudSampleTypeSupport::get_type_name();
    writer   = createDataWriter(topicNameBBS, typeName, qosLibrary, qosProfileBBS, topicBBS, publisher, participant);
    rapid_PointCloudSample_writerBBS = rapid::PointCloudSampleDataWriter::narrow(writer);
    instanceBBS = rapid::PointCloudSampleTypeSupport::create_data();
    setHeader(instanceBBS->hdr);
    instanceHandleBBS = rapid_PointCloudSample_writerBBS->register_instance(*instanceBBS);
    
    //=== Create Publication AAC =============================
    fprintf(stderr, "*** Create PointCloudConfig\n------------------------------\n");
    typeName = rapid::PointCloudConfigTypeSupport::get_type_name();
    writer   = createDataWriter(topicNameAAC, typeName, qosLibrary, qosProfileAAC, topicAAC, publisher, participant);
    
    fprintf(stderr, "narrow:\n");
    rapid_PointCloudConfig_writerAAC = rapid::PointCloudConfigDataWriter::narrow(writer);
    fprintf(stderr, "create data:\n");
    
    instanceAAC = rapid::PointCloudConfigTypeSupport::create_data();
    setPointCloudConfig(*instanceAAC);
    instanceHandleAAC = rapid_PointCloudConfig_writerAAC->register_instance(*instanceAAC);

    //=== Create Publication BBC =============================
    fprintf(stderr, "*** Create PointCloudConfig\n------------------------------\n");
    typeName = rapid::PointCloudConfigTypeSupport::get_type_name();
    writer   = createDataWriter(topicNameBBC, typeName, qosLibrary, qosProfileBBC, topicBBC, publisher, participant);
    rapid_PointCloudConfig_writerBBC = rapid::PointCloudConfigDataWriter::narrow(writer);
    instanceBBC = rapid::PointCloudConfigTypeSupport::create_data();
    setPointCloudConfig(*instanceBBC);
    instanceHandleBBC = rapid_PointCloudConfig_writerBBC->register_instance(*instanceBBC);

    //=== Write the Config messages ========================
    rapid_PointCloudConfig_writerAAC->write(*instanceAAC, instanceHandleAAC);
    rapid_PointCloudConfig_writerBBC->write(*instanceBBC, instanceHandleBBC);

    //=== Main loop ========================================
    for (count=0; (sample_count == 0) || (count < sample_count); ++count) {

        printf("Writing rapid::PointCloudSample, count %d\n", count);

        updatePointCloudSample(*instanceAAS, 5000+rand()%213, -10);
        retcode = rapid_PointCloudSample_writerAAS->write(*instanceAAS, instanceHandleAAS);
        if (retcode != RETCODE_OK) {
            printf("write error %d\n", retcode);
        }
        
        updatePointCloudSample(*instanceBBS, 8000+rand()%411,  10);
        retcode = rapid_PointCloudSample_writerBBS->write(*instanceBBS, instanceHandleBBS);
        if (retcode != RETCODE_OK) {
            printf("write error %d\n", retcode);
        }
        

        NDDSUtility::sleep(send_period);
    }


    retcode = rapid_PointCloudSample_writerAAS->unregister_instance(
        *instanceAAS, instanceHandleAAS);
    if (retcode != RETCODE_OK) {
        printf("unregister instance error %d\n", retcode);
    }

    /* Delete data sample */
    retcode = rapid::PointCloudSampleTypeSupport::delete_data(instanceAAS);
    if (retcode != RETCODE_OK) {
        printf("rapid::PointCloudSampleTypeSupport::delete_data error %d\n", retcode);
    }

    /* Delete all entities */
    return publisher_shutdown(participant);
}

int main(int argc, char *argv[])
{
    int domainId = 13;
    int sample_count = 0; /* infinite loop */

    if (argc >= 2) {
        domainId = atoi(argv[1]);
    }
    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    if(true) {
      NDDSConfigLogger::get_instance()->
          set_verbosity_by_category(NDDS_CONFIG_LOG_CATEGORY_API, 
                                    NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
    }
    
    return publisher_main(domainId, sample_count);
}

