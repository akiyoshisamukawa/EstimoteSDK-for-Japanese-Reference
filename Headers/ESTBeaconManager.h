//
//  ESTBeaconManager.h
//  EstimoteSDK7
//
//  Version : 1.0.0
//  Created by Marcin Klimek on 9/18/13.
//  Copyright (c) 2013 Estimote. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "ESTBeaconRegion.h"
#import "ESTBeacon.h"

@class ESTBeaconManager;

/**
 
 ESTBeaconManagerDelegateプロトコルは、関連するイベントに対応するためのデリゲートメソッドを定義します。
 */

@protocol ESTBeaconManagerDelegate <NSObject>

@optional

/**
 * デリゲートメソッドは至る所で呼び出されます
 * ESTBeaconオブジェクトで表され、検出されたすべてのビーコンのNSArrayを取得することができます。
 *
 * @param manager estimote beacon manager
 * @param beacons all beacons as ESTBeacon objects
 * @param region estimote beacon region
 *
 * @return void
 */
- (void)beaconManager:(ESTBeaconManager *)manager
      didRangeBeacons:(NSArray *)beacons
             inRegion:(ESTBeaconRegion *)region;

/**
 * 特定のリージョンの検出に失敗した場合に呼び出されるデリゲートメソッド
 * 関連するNSErrorオブジェクトが返される
 *
 * @param manager estimote beacon manager
 * @param region estimote beacon region
 * @param error object containing error info
 *
 * @return void
 */
-(void)beaconManager:(ESTBeaconManager *)manager
rangingBeaconsDidFailForRegion:(ESTBeaconRegion *)region
           withError:(NSError *)error;


/**
 * 特定のリージョンの監視時に失敗した場合に呼び出されるデリゲートメソッド
 * 関連するNSErrorオブジェクトが返される
 *
 * @param manager estimote beacon manager
 * @param region estimote beacon region
 * @param error object containing error info
 *
 * @return void
 */
-(void)beaconManager:(ESTBeaconManager *)manager
monitoringDidFailForRegion:(ESTBeaconRegion *)region
           withError:(NSError *)error;
/**
 * iOSデバイスがEstimoteビーコンの監視範囲内に入ったときに呼び出されるトリガーメソッド
 *
 * @param manager estimote beacon manager
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)beaconManager:(ESTBeaconManager *)manager
      didEnterRegion:(ESTBeaconRegion *)region;


/**
 * iOSデバイスがEstimoteビーコンの監視範囲内からいなくなったときに呼び出されるトリガーメソッド
 *
 * @param manager estimote beacon manager
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)beaconManager:(ESTBeaconManager *)manager
       didExitRegion:(ESTBeaconRegion *)region;

/**
 * requestStateForRegion: メソッドをつかってEstimoteビーコンのリージョンの状態が決まったときに呼び出されるトリガーメソッド
 *
 * @param manager estimote beacon manager
 * @param state estimote beacon region state
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)beaconManager:(ESTBeaconManager *)manager
     didDetermineState:(CLRegionState)state
             forRegion:(ESTBeaconRegion *)region;

/**
 * デバイスがiBeaconとして通知が開始されたときに呼び出されるトリガーメソッド
 *
 * @param manager estimote beacon manager
 * @param error info about any error
 *
 * @return void
 */
-(void)beaconManagerDidStartAdvertising:(ESTBeaconManager *)manager
                                  error:(NSError *)error;

/**
 * デリゲートメソッドは特定のリージョン内でCoreBluetooth frameworkを使っている ESTBeacon オブジェクトを発見して処理するためのデリゲートメソッド
 *
 * @param manager estimote beacon manager
 * @param beacons all beacons as ESTBeacon objects
 * @param region estimote beacon region
 *
 * @return void
 */
- (void)beaconManager:(ESTBeaconManager *)manager
          didDiscoverBeacons:(NSArray *)beacons
                    inRegion:(ESTBeaconRegion *)region;

/**
 * CoreBluetoothベースの検出プロセスが失敗したときにデリゲートメソッドが呼び出される。
 *
 * @param manager estimote beacon manager
 * @param region estimote beacon region
 *
 * @return void
 */
- (void)beaconManager:(ESTBeaconManager *)manager
    didFailDiscoveryInRegion:(ESTBeaconRegion *)region;

@end



/**
 
 ESTBeaconManagerクラスはハンドリング、Estimoteビーコンの構成、アプリケーションに関するイベントを取得するためのインターフェースを定義します。これらのビーコンの動作を表現するパラメータを設置するために、このクラスのインスタンスを使います。また、範囲内のすべてのビーコンを取得するためにビーコンマネージャオブジェクトを使用することができます。
 
 ビーコンマネージャオブジェクトは、次の場所に関連する活動のためのサポートを提供します：
 
 * 関心の異なる領域を監視し、ユーザがそれらの領域を（バックグラウンドモードで動作する）に入るか、または出るとき場所イベントを生成する。
 * 近くのビーコンとデバイスの熱距離の範囲の報告。
 
 */

@interface ESTBeaconManager : NSObject <CLLocationManagerDelegate>

@property (nonatomic, weak) id <ESTBeaconManagerDelegate> delegate;

/**
 近接してきたビーコンがunknownステータス（proximity == 0）の場合を回避することができる。デフォルトはNOで設定されている。
 */
@property (nonatomic) BOOL avoidUnknownStateBeacons;

@property (nonatomic, strong) ESTBeaconRegion*         virtualBeaconRegion;

/**
 * 範囲内に表示されているすべてのEstimoteビーコンを計測する
 * デリゲートメソッドの beaconManager:didRangeBeacons:inRegion: は発見したビーコンを取得するために使用されます。返されるNSArrayのはESTBeaconオブジェクトが含まれています。
 *
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)startRangingBeaconsInRegion:(ESTBeaconRegion*)region;

/**
 * 特定のリージョンの監視を開始する
 * これはバックグラウンドモードで実行されます
 * リージョンから近づくか離れるたびに適切なデリゲートメソッドとして beaconManager:beaconManager:didEnterRegion: と beaconManager:didExitRegion: が呼ばれます
 *
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)startMonitoringForRegion:(ESTBeaconRegion*)region;

/**
 * Estimoteビーコンの検出を停止する
 *
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)stopRangingBeaconsInRegion:(ESTBeaconRegion*)region;

/**
 * EstimoteビーコンリージョンのiOSの監視からアプリケーションを解除します
 *
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)stopMonitoringForRegion:(ESTBeaconRegion *)region;

/**
 * 特定のリージョンの現在のステータスを確認することができる
 *
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)requestStateForRegion:(ESTBeaconRegion *)region;

/**
 * 仮想estimoteビーコンにデバイスをオンにすることができる
 *
 * @param major minor beacon value
 * @param minor major beacon value
 * @param identifier unique identifier for you region
 *
 * @return void
 */
-(void)startAdvertisingWithMajor:(ESTBeaconMajorValue)major
                       withMinor:(ESTBeaconMinorValue)minor
                  withIdentifier:(NSString*)identifier;


/**
 * ビーコンの通知を停止する
 *
 * @return void
 */
-(void)stopAdvertising;

/**
 * CoreBluetoothフレームワークに基づいてビーコン検出プロセスを開始します
 * このメソッドはiBeaconsとして通知されていない古いビーコン発見のために便利です
 *
 * @param region estimote beacon region
 *
 * @return void
 */
-(void)startEstimoteBeaconsDiscoveryForRegion:(ESTBeaconRegion*)region;


/**
 * CoreBluetoothベースビーコン検出プロセスを停止します
 *
 * @return void
 */
-(void)stopEstimoteBeaconDiscovery;

@end

