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
/// The Key Cells for results on Key of scan
/// </summary>
public partial class kCells : TBase
{
  private List<byte[]> _k;
  private List<KCell> _cells;

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


  public Isset __isset;
  public struct Isset
  {
    public bool k;
    public bool cells;
  }

  public kCells()
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
                TList _list64 = await iprot.ReadListBeginAsync(cancellationToken);
                K = new List<byte[]>(_list64.Count);
                for(int _i65 = 0; _i65 < _list64.Count; ++_i65)
                {
                  byte[] _elem66;
                  _elem66 = await iprot.ReadBinaryAsync(cancellationToken);
                  K.Add(_elem66);
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
                TList _list67 = await iprot.ReadListBeginAsync(cancellationToken);
                Cells = new List<KCell>(_list67.Count);
                for(int _i68 = 0; _i68 < _list67.Count; ++_i68)
                {
                  KCell _elem69;
                  _elem69 = new KCell();
                  await _elem69.ReadAsync(iprot, cancellationToken);
                  Cells.Add(_elem69);
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

  public async Task WriteAsync(TProtocol oprot, CancellationToken cancellationToken)
  {
    oprot.IncrementRecursionDepth();
    try
    {
      var struc = new TStruct("kCells");
      await oprot.WriteStructBeginAsync(struc, cancellationToken);
      var field = new TField();
      if (K != null && __isset.k)
      {
        field.Name = "k";
        field.Type = TType.List;
        field.ID = 1;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.String, K.Count), cancellationToken);
          foreach (byte[] _iter70 in K)
          {
            await oprot.WriteBinaryAsync(_iter70, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Cells != null && __isset.cells)
      {
        field.Name = "cells";
        field.Type = TType.List;
        field.ID = 2;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.Struct, Cells.Count), cancellationToken);
          foreach (KCell _iter71 in Cells)
          {
            await _iter71.WriteAsync(oprot, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
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
    var other = that as kCells;
    if (other == null) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.k == other.__isset.k) && ((!__isset.k) || (System.Object.Equals(K, other.K))))
      && ((__isset.cells == other.__isset.cells) && ((!__isset.cells) || (TCollections.Equals(Cells, other.Cells))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.k)
        hashcode = (hashcode * 397) + K.GetHashCode();
      if(__isset.cells)
        hashcode = (hashcode * 397) + TCollections.GetHashCode(Cells);
    }
    return hashcode;
  }

  public override string ToString()
  {
    var sb = new StringBuilder("kCells(");
    bool __first = true;
    if (K != null && __isset.k)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("K: ");
      sb.Append(K);
    }
    if (Cells != null && __isset.cells)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Cells: ");
      sb.Append(Cells);
    }
    sb.Append(")");
    return sb.ToString();
  }
}

