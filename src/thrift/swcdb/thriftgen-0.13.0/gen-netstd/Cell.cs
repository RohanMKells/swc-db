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
/// The Cell for results list of scan
/// </summary>
public partial class Cell : TBase
{
  private string _c;
  private List<byte[]> _k;
  private long _ts;
  private byte[] _v;

  /// <summary>
  /// The Column Name
  /// </summary>
  public string C
  {
    get
    {
      return _c;
    }
    set
    {
      __isset.c = true;
      this._c = value;
    }
  }

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
  /// The Cell Timestamp
  /// </summary>
  public long Ts
  {
    get
    {
      return _ts;
    }
    set
    {
      __isset.ts = true;
      this._ts = value;
    }
  }

  /// <summary>
  /// The Cell Value
  /// </summary>
  public byte[] V
  {
    get
    {
      return _v;
    }
    set
    {
      __isset.v = true;
      this._v = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool c;
    public bool k;
    public bool ts;
    public bool v;
  }

  public Cell()
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
            if (field.Type == TType.String)
            {
              C = await iprot.ReadStringAsync(cancellationToken);
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
                TList _list48 = await iprot.ReadListBeginAsync(cancellationToken);
                K = new List<byte[]>(_list48.Count);
                for(int _i49 = 0; _i49 < _list48.Count; ++_i49)
                {
                  byte[] _elem50;
                  _elem50 = await iprot.ReadBinaryAsync(cancellationToken);
                  K.Add(_elem50);
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
            if (field.Type == TType.I64)
            {
              Ts = await iprot.ReadI64Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 4:
            if (field.Type == TType.String)
            {
              V = await iprot.ReadBinaryAsync(cancellationToken);
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
      var struc = new TStruct("Cell");
      await oprot.WriteStructBeginAsync(struc, cancellationToken);
      var field = new TField();
      if (C != null && __isset.c)
      {
        field.Name = "c";
        field.Type = TType.String;
        field.ID = 1;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await oprot.WriteStringAsync(C, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (K != null && __isset.k)
      {
        field.Name = "k";
        field.Type = TType.List;
        field.ID = 2;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.String, K.Count), cancellationToken);
          foreach (byte[] _iter51 in K)
          {
            await oprot.WriteBinaryAsync(_iter51, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (__isset.ts)
      {
        field.Name = "ts";
        field.Type = TType.I64;
        field.ID = 3;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await oprot.WriteI64Async(Ts, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (V != null && __isset.v)
      {
        field.Name = "v";
        field.Type = TType.String;
        field.ID = 4;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await oprot.WriteBinaryAsync(V, cancellationToken);
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
    var other = that as Cell;
    if (other == null) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.c == other.__isset.c) && ((!__isset.c) || (System.Object.Equals(C, other.C))))
      && ((__isset.k == other.__isset.k) && ((!__isset.k) || (System.Object.Equals(K, other.K))))
      && ((__isset.ts == other.__isset.ts) && ((!__isset.ts) || (System.Object.Equals(Ts, other.Ts))))
      && ((__isset.v == other.__isset.v) && ((!__isset.v) || (TCollections.Equals(V, other.V))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.c)
        hashcode = (hashcode * 397) + C.GetHashCode();
      if(__isset.k)
        hashcode = (hashcode * 397) + K.GetHashCode();
      if(__isset.ts)
        hashcode = (hashcode * 397) + Ts.GetHashCode();
      if(__isset.v)
        hashcode = (hashcode * 397) + V.GetHashCode();
    }
    return hashcode;
  }

  public override string ToString()
  {
    var sb = new StringBuilder("Cell(");
    bool __first = true;
    if (C != null && __isset.c)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("C: ");
      sb.Append(C);
    }
    if (K != null && __isset.k)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("K: ");
      sb.Append(K);
    }
    if (__isset.ts)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Ts: ");
      sb.Append(Ts);
    }
    if (V != null && __isset.v)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("V: ");
      sb.Append(V);
    }
    sb.Append(")");
    return sb.ToString();
  }
}

