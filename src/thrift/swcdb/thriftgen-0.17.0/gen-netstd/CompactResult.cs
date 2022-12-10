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
/// The Compact Result
/// </summary>
public partial class CompactResult : TBase
{
  private long _cid;
  private int _err;

  /// <summary>
  /// Column ID
  /// </summary>
  public long Cid
  {
    get
    {
      return _cid;
    }
    set
    {
      __isset.cid = true;
      this._cid = value;
    }
  }

  /// <summary>
  /// Error
  /// </summary>
  public int Err
  {
    get
    {
      return _err;
    }
    set
    {
      __isset.err = true;
      this._err = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool cid;
    public bool err;
  }

  public CompactResult()
  {
  }

  public CompactResult DeepCopy()
  {
    var tmp554 = new CompactResult();
    if(__isset.cid)
    {
      tmp554.Cid = this.Cid;
    }
    tmp554.__isset.cid = this.__isset.cid;
    if(__isset.err)
    {
      tmp554.Err = this.Err;
    }
    tmp554.__isset.err = this.__isset.err;
    return tmp554;
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
            if (field.Type == TType.I64)
            {
              Cid = await iprot.ReadI64Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 2:
            if (field.Type == TType.I32)
            {
              Err = await iprot.ReadI32Async(cancellationToken);
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
      var tmp555 = new TStruct("CompactResult");
      await oprot.WriteStructBeginAsync(tmp555, cancellationToken);
      var tmp556 = new TField();
      if(__isset.cid)
      {
        tmp556.Name = "cid";
        tmp556.Type = TType.I64;
        tmp556.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp556, cancellationToken);
        await oprot.WriteI64Async(Cid, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.err)
      {
        tmp556.Name = "err";
        tmp556.Type = TType.I32;
        tmp556.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp556, cancellationToken);
        await oprot.WriteI32Async(Err, cancellationToken);
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
    if (!(that is CompactResult other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.cid == other.__isset.cid) && ((!__isset.cid) || (global::System.Object.Equals(Cid, other.Cid))))
      && ((__isset.err == other.__isset.err) && ((!__isset.err) || (global::System.Object.Equals(Err, other.Err))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.cid)
      {
        hashcode = (hashcode * 397) + Cid.GetHashCode();
      }
      if(__isset.err)
      {
        hashcode = (hashcode * 397) + Err.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp557 = new StringBuilder("CompactResult(");
    int tmp558 = 0;
    if(__isset.cid)
    {
      if(0 < tmp558++) { tmp557.Append(", "); }
      tmp557.Append("Cid: ");
      Cid.ToString(tmp557);
    }
    if(__isset.err)
    {
      if(0 < tmp558++) { tmp557.Append(", "); }
      tmp557.Append("Err: ");
      Err.ToString(tmp557);
    }
    tmp557.Append(')');
    return tmp557.ToString();
  }
}

