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
/// The Column Cell for results on Columns of scan
/// </summary>
public partial class CCell : TBase
{
  private List<byte[]> _k;
  private long _ts;
  private byte[] _v;

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
    public bool k;
    public bool ts;
    public bool v;
  }

  public CCell()
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
                TList _list52 = await iprot.ReadListBeginAsync(cancellationToken);
                K = new List<byte[]>(_list52.Count);
                for(int _i53 = 0; _i53 < _list52.Count; ++_i53)
                {
                  byte[] _elem54;
                  _elem54 = await iprot.ReadBinaryAsync(cancellationToken);
                  K.Add(_elem54);
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
            if (field.Type == TType.I64)
            {
              Ts = await iprot.ReadI64Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 3:
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
      var struc = new TStruct("CCell");
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
          foreach (byte[] _iter55 in K)
          {
            await oprot.WriteBinaryAsync(_iter55, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (__isset.ts)
      {
        field.Name = "ts";
        field.Type = TType.I64;
        field.ID = 2;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await oprot.WriteI64Async(Ts, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (V != null && __isset.v)
      {
        field.Name = "v";
        field.Type = TType.String;
        field.ID = 3;
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
    var other = that as CCell;
    if (other == null) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.k == other.__isset.k) && ((!__isset.k) || (System.Object.Equals(K, other.K))))
      && ((__isset.ts == other.__isset.ts) && ((!__isset.ts) || (System.Object.Equals(Ts, other.Ts))))
      && ((__isset.v == other.__isset.v) && ((!__isset.v) || (TCollections.Equals(V, other.V))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
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
    var sb = new StringBuilder("CCell(");
    bool __first = true;
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

