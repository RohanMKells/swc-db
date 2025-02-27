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
/// The Counter column type Cell for results on Columns of scan
/// </summary>
public partial class CCellCounter : TBase
{
  private List<byte[]> _k;
  private long _ts;
  private long _v;
  private long _eq;

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
  /// The Cell Counter Value
  /// </summary>
  public long V
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
  /// The Counter EQ since ts
  /// </summary>
  public long Eq
  {
    get
    {
      return _eq;
    }
    set
    {
      __isset.eq = true;
      this._eq = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool k;
    public bool ts;
    public bool v;
    public bool eq;
  }

  public CCellCounter()
  {
  }

  public CCellCounter DeepCopy()
  {
    var tmp438 = new CCellCounter();
    if((K != null) && __isset.k)
    {
      tmp438.K = this.K.DeepCopy();
    }
    tmp438.__isset.k = this.__isset.k;
    if(__isset.ts)
    {
      tmp438.Ts = this.Ts;
    }
    tmp438.__isset.ts = this.__isset.ts;
    if(__isset.v)
    {
      tmp438.V = this.V;
    }
    tmp438.__isset.v = this.__isset.v;
    if(__isset.eq)
    {
      tmp438.Eq = this.Eq;
    }
    tmp438.__isset.eq = this.__isset.eq;
    return tmp438;
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
                var _list439 = await iprot.ReadListBeginAsync(cancellationToken);
                K = new List<byte[]>(_list439.Count);
                for(int _i440 = 0; _i440 < _list439.Count; ++_i440)
                {
                  byte[] _elem441;
                  _elem441 = await iprot.ReadBinaryAsync(cancellationToken);
                  K.Add(_elem441);
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
            if (field.Type == TType.I64)
            {
              V = await iprot.ReadI64Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 4:
            if (field.Type == TType.I64)
            {
              Eq = await iprot.ReadI64Async(cancellationToken);
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
      var tmp442 = new TStruct("CCellCounter");
      await oprot.WriteStructBeginAsync(tmp442, cancellationToken);
      var tmp443 = new TField();
      if((K != null) && __isset.k)
      {
        tmp443.Name = "k";
        tmp443.Type = TType.List;
        tmp443.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp443, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.String, K.Count), cancellationToken);
        foreach (byte[] _iter444 in K)
        {
          await oprot.WriteBinaryAsync(_iter444, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.ts)
      {
        tmp443.Name = "ts";
        tmp443.Type = TType.I64;
        tmp443.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp443, cancellationToken);
        await oprot.WriteI64Async(Ts, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.v)
      {
        tmp443.Name = "v";
        tmp443.Type = TType.I64;
        tmp443.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp443, cancellationToken);
        await oprot.WriteI64Async(V, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.eq)
      {
        tmp443.Name = "eq";
        tmp443.Type = TType.I64;
        tmp443.ID = 4;
        await oprot.WriteFieldBeginAsync(tmp443, cancellationToken);
        await oprot.WriteI64Async(Eq, cancellationToken);
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
    if (!(that is CCellCounter other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.k == other.__isset.k) && ((!__isset.k) || (global::System.Object.Equals(K, other.K))))
      && ((__isset.ts == other.__isset.ts) && ((!__isset.ts) || (global::System.Object.Equals(Ts, other.Ts))))
      && ((__isset.v == other.__isset.v) && ((!__isset.v) || (global::System.Object.Equals(V, other.V))))
      && ((__isset.eq == other.__isset.eq) && ((!__isset.eq) || (global::System.Object.Equals(Eq, other.Eq))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if((K != null) && __isset.k)
      {
        hashcode = (hashcode * 397) + K.GetHashCode();
      }
      if(__isset.ts)
      {
        hashcode = (hashcode * 397) + Ts.GetHashCode();
      }
      if(__isset.v)
      {
        hashcode = (hashcode * 397) + V.GetHashCode();
      }
      if(__isset.eq)
      {
        hashcode = (hashcode * 397) + Eq.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp445 = new StringBuilder("CCellCounter(");
    int tmp446 = 0;
    if((K != null) && __isset.k)
    {
      if(0 < tmp446++) { tmp445.Append(", "); }
      tmp445.Append("K: ");
      K.ToString(tmp445);
    }
    if(__isset.ts)
    {
      if(0 < tmp446++) { tmp445.Append(", "); }
      tmp445.Append("Ts: ");
      Ts.ToString(tmp445);
    }
    if(__isset.v)
    {
      if(0 < tmp446++) { tmp445.Append(", "); }
      tmp445.Append("V: ");
      V.ToString(tmp445);
    }
    if(__isset.eq)
    {
      if(0 < tmp446++) { tmp445.Append(", "); }
      tmp445.Append("Eq: ");
      Eq.ToString(tmp445);
    }
    tmp445.Append(')');
    return tmp445.ToString();
  }
}

