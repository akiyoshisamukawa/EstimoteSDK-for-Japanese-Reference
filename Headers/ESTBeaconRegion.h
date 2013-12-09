//
//  ESTBeaconRegion.h
//  EstimoteSDK7
//
//  Version : 1.0.0
//  Created by Marcin Klimek on 9/21/13.
//  Copyright (c) 2013 Estimote. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/*
 *  ESTBeaconMajorValue
 *
 *  Discussion:
 *    Type represents the most significant value in a beacon.
 *
 */
typedef uint16_t ESTBeaconMajorValue;

/*
 *  ESTBeaconMinorValue
 *
 *  Discussion:
 *    Type represents the least significant value in a beacon.
 *
 */
typedef uint16_t ESTBeaconMinorValue;


/**
 
 ESTBeaconRegionオブジェクトは、位置情報とは対照的に、Bluetoothビーコンの近接距離に応じた領域の種類を定義している。ビーコン領域は、その識別情報とあなたが提供する情報とが一致するデバイスを探します。そのデバイスが範囲内になると、この領域は適切な通知の配信をトリガーします。
 
 次の2つの方法でビーコン領域を監視することができます。ロケーションマネージャオブジェクトのメソッド：デバイスがビーコンの付近を出入りするときに通知を受け取るには、startMonitoringForRegionを使用しています。ビーコンが距離に応じて変化したときの通知を受信する方法：ビーコンが範囲内にある間は、startRangingBeaconsInRegionを呼び出すことができます。
 
 ESTBeaconRegionは、Estimoteクラウドプラットフォームでサポートされている領域を初期化することができ、これは基本的なCLBeaconRegion Core Locationオブジェクトを継承しています。
 
 */
@interface ESTBeaconRegion : CLBeaconRegion

/**
 * Estimoteビーコン域を初期化します。メジャーとマイナーの値はワイルドカードになります。
 *
 * @param identifier Region identifier
 * @return Initialized ESTBeaconRegion object
 **/
- (id)initRegionWithIdentifier:(NSString *)identifier;

/**
 * メジャーな値を持つEstimoteビーコン領域を初期化します。マイナー値はワイルドカードになります。
 *
 * @param major minor location value
 * @param identifier Region identifier
 * @return Initialized ESTBeaconRegion object
 **/
- (id)initRegionWithMajor:(ESTBeaconMajorValue)major identifier:(NSString *)identifier;

/**
 * メジャーとマイナーの値によって識別したEstimoteビーコン領域を初期化します。
 *
 * @param major minor location value
 * @param minor minor location value
 * @param identifier Region identifier
 * @return Initialized ESTBeaconRegion object
 **/
- (id)initRegionWithMajor:(ESTBeaconMajorValue)major minor:(ESTBeaconMinorValue)minor identifier:(NSString *)identifier;

@end
