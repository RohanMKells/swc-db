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


public partial class SpecUpdateOP : TBase
{
  private UpdateOP _op;
  private int _pos;

  /// <summary>
  /// The Operation of update
  /// 
  /// <seealso cref="global::.UpdateOP"/>
  /// </summary>
  public UpdateOP Op
  {
    get
    {
      return _op;
    }
    set
    {
      __isset.op = true;
      this._op = value;
    }
  }

  /// <summary>
  /// The position/index of INSERT and OVERWRITE update operations
  /// </summary>
  public int Pos
  {
    get
    {
      return _pos;
    }
    set
    {
      __isset.pos = true;
      this._pos = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool op;
    public bool pos;
  }

  public SpecUpdateOP()
  {
  }

  public SpecUpdateOP DeepCopy()
  {
    var tmp55 = new SpecUpdateOP();
    if(__isset.op)
    {
      tmp55.Op = this.Op;
    }
    tmp55.__isset.op = this.__isset.op;
    if(__isset.pos)
    {
      tmp55.Pos = this.Pos;
    }
    tmp55.__isset.pos = this.__isset.pos;
    return tmp55;
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
              Op = (UpdateOP)await iprot.ReadI32Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 2:
            if (field.Type == TType.I32)
            {
              Pos = await iprot.ReadI32Async(cancellationToken);
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
      var tmp56 = new TStruct("SpecUpdateOP");
      await oprot.WriteStructBeginAsync(tmp56, cancellationToken);
      var tmp57 = new TField();
      if(__isset.op)
      {
        tmp57.Name = "op";
        tmp57.Type = TType.I32;
        tmp57.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp57, cancellationToken);
        await oprot.WriteI32Async((int)Op, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.pos)
      {
        tmp57.Name = "pos";
        tmp57.Type = TType.I32;
        tmp57.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp57, cancellationToken);
        await oprot.WriteI32Async(Pos, cancellationToken);
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
    if (!(that is SpecUpdateOP other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.op == other.__isset.op) && ((!__isset.op) || (global::System.Object.Equals(Op, other.Op))))
      && ((__isset.pos == other.__isset.pos) && ((!__isset.pos) || (global::System.Object.Equals(Pos, other.Pos))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.op)
      {
        hashcode = (hashcode * 397) + Op.GetHashCode();
      }
      if(__isset.pos)
      {
        hashcode = (hashcode * 397) + Pos.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp58 = new StringBuilder("SpecUpdateOP(");
    int tmp59 = 0;
    if(__isset.op)
    {
      if(0 < tmp59++) { tmp58.Append(", "); }
      tmp58.Append("Op: ");
      Op.ToString(tmp58);
    }
    if(__isset.pos)
    {
      if(0 < tmp59++) { tmp58.Append(", "); }
      tmp58.Append("Pos: ");
      Pos.ToString(tmp58);
    }
    tmp58.Append(')');
    return tmp58.ToString();
  }
}

