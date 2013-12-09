//
//  ESTBeacon.h
//  EstimoteSDK7
//
//  Version : 1.0.0
//  Created by Marcin Klimek on 9/19/13.
//  Copyright (c) 2013 Estimote. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "ESTBeaconDefinitions.h"

@class ESTBeacon;

////////////////////////////////////////////////////////////////////
// Estimote beacon delegate protocol


/**
 
 ESTBeaconDelegateは、ビーコン接続デリゲートメソッドを定義しています。これを定義する必要がある、接続は非同期処理で行われる。beaconDidDisconnectWith：メソッドは前のアクションなしで呼び出すことができます。
 
 */

@protocol ESTBeaconDelegate <NSObject>

@optional

/**
 * ビーコン接続でエラーが発生した場合に表示するデリゲートメソッド
 *
 * @param beacon reference to beacon object
 * @param error information about reason of error
 *
 * @return void
 */
- (void)beaconConnectionDidFail:(ESTBeacon*)beacon withError:(NSError*)error;

/**
 * ビーコン接続が成功した場合に表示するデリゲートメソッド
 *
 * @param beacon reference to beacon object
 *
 * @return void
 */
- (void)beaconConnectionDidSucceeded:(ESTBeacon*)beacon;

/**
 * ビーコンとデバイスの接続が切断された場合に表示するデリゲートメソッド
 *
 * @param beacon reference to beacon object
 * @param error information about reason of error
 *
 * @return void
 */
- (void)beaconDidDisconnect:(ESTBeacon*)beacon withError:(NSError*)error;

@end


////////////////////////////////////////////////////////////////////
// Interface definition

/**
 
 ESTBeaconクラスは地域の監視中に発生したビーコンを表しています。あなたが直接このクラスのインスタンスを作成する必要はありません。ESTBeaconManagerオブジェクトは、それに関連付けられたデリゲートオブジェクトに遭遇したビーコンを報告します。あなたが遭遇したビーコンを識別するためにビーコンオブジェクト内の情報を使用することができます。
 
 
 ESTBeaconクラスは基本アップルのCLBeaconオブジェクト参照だけでなく、いくつかの追加機能が含まれています。それは、その特性を読み取り/書き込みにはEstimoteビーコンと接続することでできます。
 
 */

@interface ESTBeacon : NSObject

@property (nonatomic)           ESTBeaconFirmwareState  firmwareState;
@property (nonatomic)           id <ESTBeaconDelegate>  delegate;

/////////////////////////////////////////////////////
// bluetooth beacon available when used with
// startEstimoteBeaconsDiscoveryForRegion:

@property (nonatomic, strong)   CBPeripheral*           peripheral;
@property (nonatomic, strong)   NSString*               macAddress;
@property (nonatomic, strong)   NSNumber*               measuredPower;
@property (nonatomic, strong)   NSNumber*               major;
@property (nonatomic, strong)   NSNumber*               minor;
@property (nonatomic, strong)   NSNumber*               rssi;

/////////////////////////////////////////////////////
// properties filled when read characteristic

@property (nonatomic, strong)   NSNumber*               power;
@property (nonatomic, strong)   NSNumber*               frequency;
@property (nonatomic, strong)   NSNumber*               batteryLevel;

@property (nonatomic, strong)   NSString*               hardwareVersion;
@property (nonatomic, strong)   NSString*               firmwareVersion;

/////////////////////////////////////////////////////
// core location properties

@property (nonatomic, strong)   CLBeacon*               ibeacon;


@property (nonatomic, readonly)   BOOL                  isConnected;


/**
 * 特定のビーコンにデバイスを接続します
 * 接続にはメジャー、マイナー、強さ、周波数の値を変更する必要があります
 *
 * @return void
 */
-(void)connectToBeacon;

/**
 * 特定のビーコンを使用してデバイスを切断する
 *
 * @return void
 */
-(void)disconnectBeacon;

/**
 * 接続しているビーコンのメジャー番号を読み取る
 *
 * @param completion block with major value as param
 *
 * @return void
 */
- (void)readBeaconMajorWithCompletion:(ESTUnsignedCompletionBlock)completion;

/**
 * 接続しているビーコンのマイナー番号を読み取る
 *
 * @param completion block with minor value as param
 *
 * @return void
 */
- (void)readBeaconMinorWithCompletion:(ESTUnsignedCompletionBlock)completion;

/**
 * 接続しているビーコンのマイナー番号と周波数を読みとる
 *
 * @param completion block with frequency value as param
 *
 * @return void
 */
- (void)readBeaconFrequencyWithCompletion:(ESTUnsignedCompletionBlock)completion;


/**
 * 接続しているビーコンの強さを読み取る
 *
 * @param completion block with power value as param
 *
 * @return float value of beacon power
 */
- (void)readBeaconPowerWithCompletion:(ESTUnsignedCompletionBlock)completion;

/**
 * 接続しているビーコンのバッテリーを読み取る
 *
 * @param completion block with battery level value as param
 *
 * @return void
 */
- (void)readBeaconBatteryWithCompletion:(ESTUnsignedCompletionBlock)completion;

/**
 * 接続しているビーコンのファームウェアバージョンを読み取る
 *
 * @param completion block with firmware version value as param
 *
 * @return void
 */
- (void)readBeaconFirmwareVersionWithCompletion:(ESTStringCompletionBlock)completion;

/**
 * 接続しているビーコンのハードウェアバージョンを読み取る
 *
 * @param completion block with hardware version value as param
 *
 * @return void
 */
- (void)readBeaconHardwareVersionWithCompletion:(ESTStringCompletionBlock)completion;


/**
 * 接続しているビーコンのメジャー番号を書き込む
 *
 * @param major major beacon value
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)writeBeaconMajor:(short)major withCompletion:(ESTUnsignedCompletionBlock)completion;

/**
 * 接続しているビーコンのマイナー番号を書き込む
 *
 * @param minor minor beacon value
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)writeBeaconMinor:(short)minor withCompletion:(ESTUnsignedCompletionBlock)completion;

/**
 * 接続しているビーコンの周波数を書き込む
 *
 * @param frequency advertising beacon frequency
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)writeBeaconFrequency:(short)frequency withCompletion:(ESTUnsignedCompletionBlock)completion;


/**
 * 接続しているビーコンの強さを書き込む
 *
 * @param power advertising beacon power
 * @param completion block handling operation completion
 *
 * @return void
 */
- (void)writeBeaconPower:(ESTBeaconPower)power withCompletion:(ESTUnsignedCompletionBlock)completion;


/**
 * 新しいファームウェアバージョンは、接続されているビーコンのダウンロードとアップデートファームウェアで使用できるかどうかを確認します
 * これにはインターネット接続が必要になります
 *
 * @param progress Block handling operation progress
 * @param completion Block handling operation completion
 *
 * @return void
 */
-(void)updateBeaconFirmwareWithProgress:(ESTStringCompletionBlock)progress
                          andCompletion:(ESTCompletionBlock)completion;

@end
