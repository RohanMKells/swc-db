/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;


/**
 * Data Encoding Types
 */
public enum EncodingType implements org.apache.thrift.TEnum {
  /**
   * Encoding by Ranger DEFAULT configurations
   */
  DEFAULT(0),
  /**
   * No Encoding
   */
  PLAIN(1),
  /**
   * Encode with zlib
   */
  ZLIB(2),
  /**
   * Encode with snappy
   */
  SNAPPY(3),
  /**
   * Encode with zstandard
   */
  ZSTD(4),
  /**
   * Unrecognized Type
   */
  UNKNOWN(255);

  private final int value;

  private EncodingType(int value) {
    this.value = value;
  }

  /**
   * Get the integer value of this enum value, as defined in the Thrift IDL.
   */
  @Override
  public int getValue() {
    return value;
  }

  /**
   * Find a the enum type by its integer value, as defined in the Thrift IDL.
   * @return null if the value is not found.
   */
  @org.apache.thrift.annotation.Nullable
  public static EncodingType findByValue(int value) { 
    switch (value) {
      case 0:
        return DEFAULT;
      case 1:
        return PLAIN;
      case 2:
        return ZLIB;
      case 3:
        return SNAPPY;
      case 4:
        return ZSTD;
      case 255:
        return UNKNOWN;
      default:
        return null;
    }
  }
}
