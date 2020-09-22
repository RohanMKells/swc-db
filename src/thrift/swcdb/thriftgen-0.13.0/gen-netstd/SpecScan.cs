/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using Thrift;
using Thrift.Collections;

using Thrift.Protocol;
using Thrift.Protocol.Entities;
using Thrift.Protocol.Utilities;
using Thrift.Transport;
using Thrift.Transport.Client;
using Thrift.Transport.Server;
using Thrift.Processor;



/// <summary>
/// The Scan Specifications, the Columns-Intervals(SpecColumn/s) with global-scope Flags
/// </summary>
public partial class SpecScan : TBase
{
  private List<SpecColumn> _columns;
  private SpecFlags _flags;

  /// <summary>
  /// The Column Intervals(SpecColumn) in a list-container
  /// </summary>
  public List<SpecColumn> Columns
  {
    get
    {
      return _columns;
    }
    set
    {
      __isset.columns = true;
      this._columns = value;
    }
  }

  /// <summary>
  /// The Global Flags Specification
  /// </summary>
  public SpecFlags Flags
  {
    get
    {
      return _flags;
    }
    set
    {
      __isset.flags = true;
      this._flags = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool columns;
    public bool flags;
  }

  public SpecScan()
  {
  }

  public async Task ReadAsync(TProtocol iprot, CancellationToken cancellationToken)
  {
    iprot.IncrementRecursionDepth();
    try
    {
      TField field;
      await iprot.ReadStructBeginAsync(cancellationToken);
      while (true)
      {
        field = await iprot.ReadFieldBeginAsync(cancellationToken);
        if (field.Type == TType.Stop)
        {
          break;
        }

        switch (field.ID)
        {
          case 1:
            if (field.Type == TType.List)
            {
              {
                TList _list40 = await iprot.ReadListBeginAsync(cancellationToken);
                Columns = new List<SpecColumn>(_list40.Count);
                for(int _i41 = 0; _i41 < _list40.Count; ++_i41)
                {
                  SpecColumn _elem42;
                  _elem42 = new SpecColumn();
                  await _elem42.ReadAsync(iprot, cancellationToken);
                  Columns.Add(_elem42);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 2:
            if (field.Type == TType.Struct)
            {
              Flags = new SpecFlags();
              await Flags.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          default: 
            await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            break;
        }

        await iprot.ReadFieldEndAsync(cancellationToken);
      }

      await iprot.ReadStructEndAsync(cancellationToken);
    }
    finally
    {
      iprot.DecrementRecursionDepth();
    }
  }

  public async Task WriteAsync(TProtocol oprot, CancellationToken cancellationToken)
  {
    oprot.IncrementRecursionDepth();
    try
    {
      var struc = new TStruct("SpecScan");
      await oprot.WriteStructBeginAsync(struc, cancellationToken);
      var field = new TField();
      if (Columns != null && __isset.columns)
      {
        field.Name = "columns";
        field.Type = TType.List;
        field.ID = 1;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.Struct, Columns.Count), cancellationToken);
          foreach (SpecColumn _iter43 in Columns)
          {
            await _iter43.WriteAsync(oprot, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Flags != null && __isset.flags)
      {
        field.Name = "flags";
        field.Type = TType.Struct;
        field.ID = 2;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await Flags.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      await oprot.WriteFieldStopAsync(cancellationToken);
      await oprot.WriteStructEndAsync(cancellationToken);
    }
    finally
    {
      oprot.DecrementRecursionDepth();
    }
  }

  public override bool Equals(object that)
  {
    var other = that as SpecScan;
    if (other == null) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.columns == other.__isset.columns) && ((!__isset.columns) || (TCollections.Equals(Columns, other.Columns))))
      && ((__isset.flags == other.__isset.flags) && ((!__isset.flags) || (System.Object.Equals(Flags, other.Flags))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.columns)
        hashcode = (hashcode * 397) + TCollections.GetHashCode(Columns);
      if(__isset.flags)
        hashcode = (hashcode * 397) + Flags.GetHashCode();
    }
    return hashcode;
  }

  public override string ToString()
  {
    var sb = new StringBuilder("SpecScan(");
    bool __first = true;
    if (Columns != null && __isset.columns)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Columns: ");
      sb.Append(Columns);
    }
    if (Flags != null && __isset.flags)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Flags: ");
      sb.Append(Flags== null ? "<null>" : Flags.ToString());
    }
    sb.Append(")");
    return sb.ToString();
  }
}

