/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;


/**
 * The Cell Flag
 */
public enum Flag implements org.apache.thrift.TEnum {
  /**
   * Unknown/Undefined
   */
  NONE(0),
  /**
   * The Cell is an insert
   */
  INSERT(1),
  /**
   * The Cell is a delete versions lower-equal
   */
  DELETE_LE(2),
  /**
   * The Cell is a  delete version equal
   */
  DELETE_EQ(3);

  private final int value;

  private Flag(int value) {
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
  public static Flag findByValue(int value) { 
    switch (value) {
      case 0:
        return NONE;
      case 1:
        return INSERT;
      case 2:
        return DELETE_LE;
      case 3:
        return DELETE_EQ;
      default:
        return null;
    }
  }
}
