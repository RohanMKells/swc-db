/**
 * <auto-generated>
 * Autogenerated by Thrift Compiler (0.17.0)
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 * </auto-generated>
 */

#pragma warning disable IDE0079  // remove unnecessary pragmas
#pragma warning disable IDE0017  // object init can be simplified
#pragma warning disable IDE0028  // collection init can be simplified
#pragma warning disable IDE1006  // parts of the code use IDL spelling
#pragma warning disable CA1822   // empty DeepCopy() methods still non-static
#pragma warning disable IDE0083  // pattern matching "that is not SomeType" requires net5.0 but we still support earlier versions

/// <summary>
/// Column Value Types
/// </summary>
public enum ColumnType
{
  /// <summary>
  /// Unknown/Unrecognized Type
  /// </summary>
  UNKNOWN = 0,
  /// <summary>
  /// A Plain Column Value
  /// </summary>
  PLAIN = 1,
  /// <summary>
  /// A Counter Column Value with integrity of signed-64bit
  /// </summary>
  COUNTER_I64 = 2,
  /// <summary>
  /// A Counter Column Value with integrity of signed-32bit
  /// </summary>
  COUNTER_I32 = 3,
  /// <summary>
  /// A Counter Column Value with integrity of signed-16bit
  /// </summary>
  COUNTER_I16 = 4,
  /// <summary>
  /// A Counter Column Value with integrity of signed-8bit
  /// </summary>
  COUNTER_I8 = 5,
  /// <summary>
  /// A Serial Column Value
  /// </summary>
  SERIAL = 6,
  /// <summary>
  /// Not used - experimental
  /// </summary>
  CELL_DEFINED = 15,
}
