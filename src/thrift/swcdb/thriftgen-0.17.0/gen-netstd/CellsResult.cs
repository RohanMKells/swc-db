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
/// The Cells Results types for using with CellsGroup requests
/// </summary>
public enum CellsResult
{
  /// <summary>
  /// Correspond to result on Cells (Cells in list)
  /// </summary>
  IN_LIST = 0,
  /// <summary>
  /// Correspond to result on CCells (Columns Cells)
  /// </summary>
  ON_COLUMN = 1,
  /// <summary>
  /// Correspond to result on KCells (Keys Cells)
  /// </summary>
  ON_KEY = 2,
  /// <summary>
  /// Correspond to result on FCells (Fraction Cells)
  /// </summary>
  ON_FRACTION = 3,
}
