/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;


/**
 * The Scan options Flags Specifications for the SpecFlags 'options' bit
 */
public enum SpecFlagsOpt implements org.apache.thrift.TEnum {
  /**
   * No Flag Applied
   */
  NONE(0),
  /**
   * Cells Limit by Keys
   */
  LIMIT_BY_KEYS(1),
  /**
   * Cells Offset by Keys
   */
  OFFSET_BY_KEYS(4),
  /**
   * Select Cells Only Keys without Value data
   */
  ONLY_KEYS(8),
  /**
   * Select Cells Only with DELETE(cell-flag)
   */
  ONLY_DELETES(10);

  private final int value;

  private SpecFlagsOpt(int value) {
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
  public static SpecFlagsOpt findByValue(int value) { 
    switch (value) {
      case 0:
        return NONE;
      case 1:
        return LIMIT_BY_KEYS;
      case 4:
        return OFFSET_BY_KEYS;
      case 8:
        return ONLY_KEYS;
      case 10:
        return ONLY_DELETES;
      default:
        return null;
    }
  }
}
