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
/// The Key Cells for results on Key of scan
/// </summary>
public partial class kCells : TBase
{
  private List<byte[]> _k;
  private List<KCell> _cells;
  private List<KCellSerial> _serial_cells;

  /// <summary>
  /// The Cell Key
  /// </summary>
  public List<byte[]> K
  {
    get
    {
      return _k;
    }
    set
    {
      __isset.k = true;
      this._k = value;
    }
  }

  /// <summary>
  /// The Key's Cells, defined as KCell items in a list-container
  /// </summary>
  public List<KCell> Cells
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
  /// The Key's Serial Cells, defined as KCellSerial items in a list-container
  /// </summary>
  public List<KCellSerial> Serial_cells
  {
    get
    {
      return _serial_cells;
    }
    set
    {
      __isset.serial_cells = true;
      this._serial_cells = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool k;
    public bool cells;
    public bool serial_cells;
  }

  public kCells()
  {
  }

  public kCells DeepCopy()
  {
    var tmp478 = new kCells();
    if((K != null) && __isset.k)
    {
      tmp478.K = this.K.DeepCopy();
    }
    tmp478.__isset.k = this.__isset.k;
    if((Cells != null) && __isset.cells)
    {
      tmp478.Cells = this.Cells.DeepCopy();
    }
    tmp478.__isset.cells = this.__isset.cells;
    if((Serial_cells != null) && __isset.serial_cells)
    {
      tmp478.Serial_cells = this.Serial_cells.DeepCopy();
    }
    tmp478.__isset.serial_cells = this.__isset.serial_cells;
    return tmp478;
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
                var _list479 = await iprot.ReadListBeginAsync(cancellationToken);
                K = new List<byte[]>(_list479.Count);
                for(int _i480 = 0; _i480 < _list479.Count; ++_i480)
                {
                  byte[] _elem481;
                  _elem481 = await iprot.ReadBinaryAsync(cancellationToken);
                  K.Add(_elem481);
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
            if (field.Type == TType.List)
            {
              {
                var _list482 = await iprot.ReadListBeginAsync(cancellationToken);
                Cells = new List<KCell>(_list482.Count);
                for(int _i483 = 0; _i483 < _list482.Count; ++_i483)
                {
                  KCell _elem484;
                  _elem484 = new KCell();
                  await _elem484.ReadAsync(iprot, cancellationToken);
                  Cells.Add(_elem484);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
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
                var _list485 = await iprot.ReadListBeginAsync(cancellationToken);
                Serial_cells = new List<KCellSerial>(_list485.Count);
                for(int _i486 = 0; _i486 < _list485.Count; ++_i486)
                {
                  KCellSerial _elem487;
                  _elem487 = new KCellSerial();
                  await _elem487.ReadAsync(iprot, cancellationToken);
                  Serial_cells.Add(_elem487);
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
      var tmp488 = new TStruct("kCells");
      await oprot.WriteStructBeginAsync(tmp488, cancellationToken);
      var tmp489 = new TField();
      if((K != null) && __isset.k)
      {
        tmp489.Name = "k";
        tmp489.Type = TType.List;
        tmp489.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp489, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.String, K.Count), cancellationToken);
        foreach (byte[] _iter490 in K)
        {
          await oprot.WriteBinaryAsync(_iter490, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Cells != null) && __isset.cells)
      {
        tmp489.Name = "cells";
        tmp489.Type = TType.List;
        tmp489.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp489, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Cells.Count), cancellationToken);
        foreach (KCell _iter491 in Cells)
        {
          await _iter491.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Serial_cells != null) && __isset.serial_cells)
      {
        tmp489.Name = "serial_cells";
        tmp489.Type = TType.List;
        tmp489.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp489, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Serial_cells.Count), cancellationToken);
        foreach (KCellSerial _iter492 in Serial_cells)
        {
          await _iter492.WriteAsync(oprot, cancellationToken);
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
    if (!(that is kCells other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.k == other.__isset.k) && ((!__isset.k) || (global::System.Object.Equals(K, other.K))))
      && ((__isset.cells == other.__isset.cells) && ((!__isset.cells) || (TCollections.Equals(Cells, other.Cells))))
      && ((__isset.serial_cells == other.__isset.serial_cells) && ((!__isset.serial_cells) || (TCollections.Equals(Serial_cells, other.Serial_cells))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if((K != null) && __isset.k)
      {
        hashcode = (hashcode * 397) + K.GetHashCode();
      }
      if((Cells != null) && __isset.cells)
      {
        hashcode = (hashcode * 397) + TCollections.GetHashCode(Cells);
      }
      if((Serial_cells != null) && __isset.serial_cells)
      {
        hashcode = (hashcode * 397) + TCollections.GetHashCode(Serial_cells);
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp493 = new StringBuilder("kCells(");
    int tmp494 = 0;
    if((K != null) && __isset.k)
    {
      if(0 < tmp494++) { tmp493.Append(", "); }
      tmp493.Append("K: ");
      K.ToString(tmp493);
    }
    if((Cells != null) && __isset.cells)
    {
      if(0 < tmp494++) { tmp493.Append(", "); }
      tmp493.Append("Cells: ");
      Cells.ToString(tmp493);
    }
    if((Serial_cells != null) && __isset.serial_cells)
    {
      if(0 < tmp494++) { tmp493.Append(", "); }
      tmp493.Append("Serial_cells: ");
      Serial_cells.ToString(tmp493);
    }
    tmp493.Append(')');
    return tmp493.ToString();
  }
}

