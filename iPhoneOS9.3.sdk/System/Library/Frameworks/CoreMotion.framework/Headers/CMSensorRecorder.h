/*
 *  CMSensorRecorder.h
 *  CoreMotion
 *
 *  Copyright (c) 2015 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAccelerometer.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CMRecordedAccelerometerData
 *
 * Discussion:
 *   CMRecordedAccelerometerData contains data for each accelerometer sample.
 */
NS_CLASS_AVAILABLE(NA, 9_0) __WATCHOS_AVAILABLE(2.0) __TVOS_PROHIBITED
@interface CMRecordedAccelerometerData : CMAccelerometerData

/*
 * identifier
 *
 * Discussion:
 *   Unique identifier that identifies the batch for which the accelerometer sample
 *   was recorded in. This identifier will be monotonically increased
 *   for each new sensor batch recorded and can be used as an anchor for future queries.
 */
@property (readonly) uint64_t identifier;

/*
 * startDate
 *
 * Discussion:
 *   Wall time for when this sensor sample is recorded.
 *
 */
@property (readonly) NSDate *startDate;

@end

/*
 * CMSensorDataList
 *
 * Discussion:
 *   Allows retrospective access to sensor data via enumeration.
 *   If created with accelerometerDataFromDate:toDate:
 *   each enumeration will yield an object of type CMRecordedAccelerometerData.
 *   Due to the large number of samples that can be processed, the
 *   enumeration should not be run on the main/UI thread.
 */
NS_CLASS_AVAILABLE(NA, 9_0) __WATCHOS_AVAILABLE(2.0) __TVOS_PROHIBITED
@interface CMSensorDataList : NSObject <NSFastEnumeration>
@end

/*
 * CMSensorRecorder
 *
 * Discussion:
 *    CMSensorRecorder allows applications to record sensor data for periods
 *    during which the application is not active.  This data is then made
 *    available for later access (up to 3 days) when the application
 *    is run at a later time.
 */
NS_CLASS_AVAILABLE(NA, 9_0) __WATCHOS_AVAILABLE(2.0) __TVOS_PROHIBITED
@interface CMSensorRecorder : NSObject

/*
 * isAccelerometerRecordingAvailable
 *
 * Discussion:
 *   Determines whether accelerometer recording is available.
 */
+ (BOOL)isAccelerometerRecordingAvailable;

/*
 * isAuthorizedForRecording
 *
 * Discussion:
 *   Determines whether the application is authorized for sensor recording.
 */
+ (BOOL)isAuthorizedForRecording;

/*
 * accelerometerDataFromDate:ToDate:
 *
 * Discussion:
 *    Gives access to recorded accelerometer samples given a time range (fromDate, toDate].
 *    A total duration of 12 hours of data can be requested at any one time.  Data can be delayed
 *    for up to 3 minutes before being available for retrieval.  An instance of CMSensorDataList
 *    should only be enumerated from a single thread.
 */
- (nullable CMSensorDataList *)accelerometerDataFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;

/*
 * recordAccelerometerForDuration:
 *
 * Discussion:
 *    Starts recording accelerometer data for the duration given at 50hz.  Data can be recorded
 *    for up to 12 hours.
 */
- (void)recordAccelerometerForDuration:(NSTimeInterval)duration;

@end

NS_ASSUME_NONNULL_END
