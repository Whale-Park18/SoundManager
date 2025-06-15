#include "preset_list_model.h"

Q_INVOKABLE int PresetListModdel::rowCount(const QModelIndex& parent) const
{
    return Q_INVOKABLE int();
}

Q_INVOKABLE QVariant PresetListModdel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || index.row() >= _audioPresetList.size())
        return QVariant();

    const AudioPreset& p = _audioPresetList[index.row()];

    if (role == static_cast<int>(PresetRole::Name))
        return p.presetName.c_str();
    if (role == static_cast<int>(PresetRole::Level))
        return p.level;
    
    return Q_INVOKABLE QVariant();
}
