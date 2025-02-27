/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;


public enum UpdateOP implements org.apache.thrift.TEnum {
  /**
   * The OP supported by column-types: PLAIN, SERIAL, COUNTER. Replaces with the update value (_default as well if other OP not supported by the col-type_)
   */
  REPLACE(0),
  /**
   * The OP supported by column-types: PLAIN, SERIAL. Appends the update value to the cell's current
   */
  APPEND(1),
  /**
   * The OP supported by column-types: PLAIN, SERIAL. Prepends the update value to the cell's current
   */
  PREPEND(2),
  /**
   * The OP supported by column-type PLAIN. Inserts the update value at position in current value (appends if pos above value)
   */
  INSERT(3),
  /**
   * The OP supported by column-type PLAIN. Overwrites the current value at position with new value (appends if pos above value)
   */
  OVERWRITE(4),
  /**
   * The OP supported by column-type SERIAL. update is done by the inner serial-fields defintions
   */
  SERIAL(5);

  private final int value;

  private UpdateOP(int value) {
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
  public static UpdateOP findByValue(int value) { 
    switch (value) {
      case 0:
        return REPLACE;
      case 1:
        return APPEND;
      case 2:
        return PREPEND;
      case 3:
        return INSERT;
      case 4:
        return OVERWRITE;
      case 5:
        return SERIAL;
      default:
        return null;
    }
  }
}
