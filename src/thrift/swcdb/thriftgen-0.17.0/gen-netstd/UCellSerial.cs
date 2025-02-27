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
/// The Cell data for using with Update of SERIAL Column Type
/// </summary>
public partial class UCellSerial : TBase
{
  private Flag _f;
  private List<byte[]> _k;
  private long _ts;
  private bool _ts_desc;
  private List<CellValueSerial> _v;
  private EncodingType _encoder;

  /// <summary>
  /// The Cell Flag
  /// 
  /// <seealso cref="global::.Flag"/>
  /// </summary>
  public Flag F
  {
    get
    {
      return _f;
    }
    set
    {
      __isset.f = true;
      this._f = value;
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
  /// The Cell Timestamp in nanoseconds
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
  /// The Cell Version is in timestamp descending
  /// </summary>
  public bool Ts_desc
  {
    get
    {
      return _ts_desc;
    }
    set
    {
      __isset.ts_desc = true;
      this._ts_desc = value;
    }
  }

  /// <summary>
  /// The Serial Cell Value fields
  /// </summary>
  public List<CellValueSerial> V
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

  /// <summary>
  /// Optionally the Cell Value Encoding Type: ZLIB/SNAPPY/ZSTD
  /// 
  /// <seealso cref="global::.EncodingType"/>
  /// </summary>
  public EncodingType Encoder
  {
    get
    {
      return _encoder;
    }
    set
    {
      __isset.encoder = true;
      this._encoder = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool f;
    public bool k;
    public bool ts;
    public bool ts_desc;
    public bool v;
    public bool encoder;
  }

  public UCellSerial()
  {
  }

  public UCellSerial DeepCopy()
  {
    var tmp368 = new UCellSerial();
    if(__isset.f)
    {
      tmp368.F = this.F;
    }
    tmp368.__isset.f = this.__isset.f;
    if((K != null) && __isset.k)
    {
      tmp368.K = this.K.DeepCopy();
    }
    tmp368.__isset.k = this.__isset.k;
    if(__isset.ts)
    {
      tmp368.Ts = this.Ts;
    }
    tmp368.__isset.ts = this.__isset.ts;
    if(__isset.ts_desc)
    {
      tmp368.Ts_desc = this.Ts_desc;
    }
    tmp368.__isset.ts_desc = this.__isset.ts_desc;
    if((V != null) && __isset.v)
    {
      tmp368.V = this.V.DeepCopy();
    }
    tmp368.__isset.v = this.__isset.v;
    if(__isset.encoder)
    {
      tmp368.Encoder = this.Encoder;
    }
    tmp368.__isset.encoder = this.__isset.encoder;
    return tmp368;
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
            if (field.Type == TType.I32)
            {
              F = (Flag)await iprot.ReadI32Async(cancellationToken);
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
                var _list369 = await iprot.ReadListBeginAsync(cancellationToken);
                K = new List<byte[]>(_list369.Count);
                for(int _i370 = 0; _i370 < _list369.Count; ++_i370)
                {
                  byte[] _elem371;
                  _elem371 = await iprot.ReadBinaryAsync(cancellationToken);
                  K.Add(_elem371);
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
            if (field.Type == TType.Bool)
            {
              Ts_desc = await iprot.ReadBoolAsync(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 5:
            if (field.Type == TType.List)
            {
              {
                var _list372 = await iprot.ReadListBeginAsync(cancellationToken);
                V = new List<CellValueSerial>(_list372.Count);
                for(int _i373 = 0; _i373 < _list372.Count; ++_i373)
                {
                  CellValueSerial _elem374;
                  _elem374 = new CellValueSerial();
                  await _elem374.ReadAsync(iprot, cancellationToken);
                  V.Add(_elem374);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 6:
            if (field.Type == TType.I32)
            {
              Encoder = (EncodingType)await iprot.ReadI32Async(cancellationToken);
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
      var tmp375 = new TStruct("UCellSerial");
      await oprot.WriteStructBeginAsync(tmp375, cancellationToken);
      var tmp376 = new TField();
      if(__isset.f)
      {
        tmp376.Name = "f";
        tmp376.Type = TType.I32;
        tmp376.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp376, cancellationToken);
        await oprot.WriteI32Async((int)F, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((K != null) && __isset.k)
      {
        tmp376.Name = "k";
        tmp376.Type = TType.List;
        tmp376.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp376, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.String, K.Count), cancellationToken);
        foreach (byte[] _iter377 in K)
        {
          await oprot.WriteBinaryAsync(_iter377, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.ts)
      {
        tmp376.Name = "ts";
        tmp376.Type = TType.I64;
        tmp376.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp376, cancellationToken);
        await oprot.WriteI64Async(Ts, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.ts_desc)
      {
        tmp376.Name = "ts_desc";
        tmp376.Type = TType.Bool;
        tmp376.ID = 4;
        await oprot.WriteFieldBeginAsync(tmp376, cancellationToken);
        await oprot.WriteBoolAsync(Ts_desc, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V != null) && __isset.v)
      {
        tmp376.Name = "v";
        tmp376.Type = TType.List;
        tmp376.ID = 5;
        await oprot.WriteFieldBeginAsync(tmp376, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, V.Count), cancellationToken);
        foreach (CellValueSerial _iter378 in V)
        {
          await _iter378.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.encoder)
      {
        tmp376.Name = "encoder";
        tmp376.Type = TType.I32;
        tmp376.ID = 6;
        await oprot.WriteFieldBeginAsync(tmp376, cancellationToken);
        await oprot.WriteI32Async((int)Encoder, cancellationToken);
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
    if (!(that is UCellSerial other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.f == other.__isset.f) && ((!__isset.f) || (global::System.Object.Equals(F, other.F))))
      && ((__isset.k == other.__isset.k) && ((!__isset.k) || (global::System.Object.Equals(K, other.K))))
      && ((__isset.ts == other.__isset.ts) && ((!__isset.ts) || (global::System.Object.Equals(Ts, other.Ts))))
      && ((__isset.ts_desc == other.__isset.ts_desc) && ((!__isset.ts_desc) || (global::System.Object.Equals(Ts_desc, other.Ts_desc))))
      && ((__isset.v == other.__isset.v) && ((!__isset.v) || (global::System.Object.Equals(V, other.V))))
      && ((__isset.encoder == other.__isset.encoder) && ((!__isset.encoder) || (global::System.Object.Equals(Encoder, other.Encoder))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.f)
      {
        hashcode = (hashcode * 397) + F.GetHashCode();
      }
      if((K != null) && __isset.k)
      {
        hashcode = (hashcode * 397) + K.GetHashCode();
      }
      if(__isset.ts)
      {
        hashcode = (hashcode * 397) + Ts.GetHashCode();
      }
      if(__isset.ts_desc)
      {
        hashcode = (hashcode * 397) + Ts_desc.GetHashCode();
      }
      if((V != null) && __isset.v)
      {
        hashcode = (hashcode * 397) + V.GetHashCode();
      }
      if(__isset.encoder)
      {
        hashcode = (hashcode * 397) + Encoder.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp379 = new StringBuilder("UCellSerial(");
    int tmp380 = 0;
    if(__isset.f)
    {
      if(0 < tmp380++) { tmp379.Append(", "); }
      tmp379.Append("F: ");
      F.ToString(tmp379);
    }
    if((K != null) && __isset.k)
    {
      if(0 < tmp380++) { tmp379.Append(", "); }
      tmp379.Append("K: ");
      K.ToString(tmp379);
    }
    if(__isset.ts)
    {
      if(0 < tmp380++) { tmp379.Append(", "); }
      tmp379.Append("Ts: ");
      Ts.ToString(tmp379);
    }
    if(__isset.ts_desc)
    {
      if(0 < tmp380++) { tmp379.Append(", "); }
      tmp379.Append("Ts_desc: ");
      Ts_desc.ToString(tmp379);
    }
    if((V != null) && __isset.v)
    {
      if(0 < tmp380++) { tmp379.Append(", "); }
      tmp379.Append("V: ");
      V.ToString(tmp379);
    }
    if(__isset.encoder)
    {
      if(0 < tmp380++) { tmp379.Append(", "); }
      tmp379.Append("Encoder: ");
      Encoder.ToString(tmp379);
    }
    tmp379.Append(')');
    return tmp379.ToString();
  }
}

