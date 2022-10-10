/**
 * <auto-generated>
 * Autogenerated by Thrift Compiler (0.17.0)
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 * </auto-generated>
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using Thrift;
using Thrift.Collections;
using Thrift.Protocol;
using Thrift.Protocol.Entities;
using Thrift.Protocol.Utilities;
using Thrift.Transport;
using Thrift.Transport.Client;
using Thrift.Transport.Server;
using Thrift.Processor;


#pragma warning disable IDE0079  // remove unnecessary pragmas
#pragma warning disable IDE0017  // object init can be simplified
#pragma warning disable IDE0028  // collection init can be simplified
#pragma warning disable IDE1006  // parts of the code use IDL spelling
#pragma warning disable CA1822   // empty DeepCopy() methods still non-static
#pragma warning disable IDE0083  // pattern matching "that is not SomeType" requires net5.0 but we still support earlier versions


/// <summary>
/// The Result of 'exec_sql'
/// </summary>
public partial class Result : TBase
{
  private List<Schema> _schemas;
  private Cells _cells;
  private List<CompactResult> _compact;

  /// <summary>
  /// Set with result for 'list columns' query
  /// </summary>
  public List<Schema> Schemas
  {
    get
    {
      return _schemas;
    }
    set
    {
      __isset.schemas = true;
      this._schemas = value;
    }
  }

  /// <summary>
  /// Set with result for 'select' query
  /// </summary>
  public Cells Cells
  {
    get
    {
      return _cells;
    }
    set
    {
      __isset.cells = true;
      this._cells = value;
    }
  }

  /// <summary>
  /// Set with result for 'compact columns' query
  /// </summary>
  public List<CompactResult> Compact
  {
    get
    {
      return _compact;
    }
    set
    {
      __isset.compact = true;
      this._compact = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool schemas;
    public bool cells;
    public bool compact;
  }

  public Result()
  {
  }

  public Result DeepCopy()
  {
    var tmp498 = new Result();
    if((Schemas != null) && __isset.schemas)
    {
      tmp498.Schemas = this.Schemas.DeepCopy();
    }
    tmp498.__isset.schemas = this.__isset.schemas;
    if((Cells != null) && __isset.cells)
    {
      tmp498.Cells = (Cells)this.Cells.DeepCopy();
    }
    tmp498.__isset.cells = this.__isset.cells;
    if((Compact != null) && __isset.compact)
    {
      tmp498.Compact = this.Compact.DeepCopy();
    }
    tmp498.__isset.compact = this.__isset.compact;
    return tmp498;
  }

  public async global::System.Threading.Tasks.Task ReadAsync(TProtocol iprot, CancellationToken cancellationToken)
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
                var _list499 = await iprot.ReadListBeginAsync(cancellationToken);
                Schemas = new List<Schema>(_list499.Count);
                for(int _i500 = 0; _i500 < _list499.Count; ++_i500)
                {
                  Schema _elem501;
                  _elem501 = new Schema();
                  await _elem501.ReadAsync(iprot, cancellationToken);
                  Schemas.Add(_elem501);
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
              Cells = new Cells();
              await Cells.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 3:
            if (field.Type == TType.List)
            {
              {
                var _list502 = await iprot.ReadListBeginAsync(cancellationToken);
                Compact = new List<CompactResult>(_list502.Count);
                for(int _i503 = 0; _i503 < _list502.Count; ++_i503)
                {
                  CompactResult _elem504;
                  _elem504 = new CompactResult();
                  await _elem504.ReadAsync(iprot, cancellationToken);
                  Compact.Add(_elem504);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
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

  public async global::System.Threading.Tasks.Task WriteAsync(TProtocol oprot, CancellationToken cancellationToken)
  {
    oprot.IncrementRecursionDepth();
    try
    {
      var tmp505 = new TStruct("Result");
      await oprot.WriteStructBeginAsync(tmp505, cancellationToken);
      var tmp506 = new TField();
      if((Schemas != null) && __isset.schemas)
      {
        tmp506.Name = "schemas";
        tmp506.Type = TType.List;
        tmp506.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp506, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Schemas.Count), cancellationToken);
        foreach (Schema _iter507 in Schemas)
        {
          await _iter507.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Cells != null) && __isset.cells)
      {
        tmp506.Name = "cells";
        tmp506.Type = TType.Struct;
        tmp506.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp506, cancellationToken);
        await Cells.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Compact != null) && __isset.compact)
      {
        tmp506.Name = "compact";
        tmp506.Type = TType.List;
        tmp506.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp506, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Compact.Count), cancellationToken);
        foreach (CompactResult _iter508 in Compact)
        {
          await _iter508.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
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
    if (!(that is Result other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.schemas == other.__isset.schemas) && ((!__isset.schemas) || (global::System.Object.Equals(Schemas, other.Schemas))))
      && ((__isset.cells == other.__isset.cells) && ((!__isset.cells) || (global::System.Object.Equals(Cells, other.Cells))))
      && ((__isset.compact == other.__isset.compact) && ((!__isset.compact) || (global::System.Object.Equals(Compact, other.Compact))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if((Schemas != null) && __isset.schemas)
      {
        hashcode = (hashcode * 397) + Schemas.GetHashCode();
      }
      if((Cells != null) && __isset.cells)
      {
        hashcode = (hashcode * 397) + Cells.GetHashCode();
      }
      if((Compact != null) && __isset.compact)
      {
        hashcode = (hashcode * 397) + Compact.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp509 = new StringBuilder("Result(");
    int tmp510 = 0;
    if((Schemas != null) && __isset.schemas)
    {
      if(0 < tmp510++) { tmp509.Append(", "); }
      tmp509.Append("Schemas: ");
      Schemas.ToString(tmp509);
    }
    if((Cells != null) && __isset.cells)
    {
      if(0 < tmp510++) { tmp509.Append(", "); }
      tmp509.Append("Cells: ");
      Cells.ToString(tmp509);
    }
    if((Compact != null) && __isset.compact)
    {
      if(0 < tmp510++) { tmp509.Append(", "); }
      tmp509.Append("Compact: ");
      Compact.ToString(tmp509);
    }
    tmp509.Append(')');
    return tmp509.ToString();
  }
}

