/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;


/**
 * The Scan Interval Specs Options for the SpecIntervalPlain, SpecIntervalCounter and SpecIntervalSerial 'options' bit
 */
public enum SpecIntervalOptions implements org.apache.thrift.TEnum {
  /**
   * Update Bit Option
   */
  UPDATING(4),
  /**
   * Delete Bit Option
   */
  DELETING(8);

  private final int value;

  private SpecIntervalOptions(int value) {
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
  public static SpecIntervalOptions findByValue(int value) { 
    switch (value) {
      case 4:
        return UPDATING;
      case 8:
        return DELETING;
      default:
        return null;
    }
  }
}
